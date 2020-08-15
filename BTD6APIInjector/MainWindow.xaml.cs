using Microsoft.Win32;
using Reloaded.Injector;
using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace BTD6APIInjector
{
    public class ModCheckBox : CheckBox
    {
        public string modDir;
        public IntPtr modDllPid;
        public byte[] originalBytes;
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly string btd6Path = SteamUtils.GetGameDir(960090, "BloonsTD6");
        public MainWindow()
        {
            if (!string.IsNullOrEmpty(btd6Path))
            {
                if (!Directory.Exists(btd6Path + "\\mods"))
                {
                    Directory.CreateDirectory(btd6Path + "\\mods");
                }
                new Thread(BTD6Running)
                {
                    IsBackground = true
                }.Start();
                InitializeComponent();
            }
            else
            {
                MessageBox.Show("Could not find BTD6 Steam install! Make sure you have BTD6 installed on Steam.");
            }
        }

        public void BTD6Running()
        {
            while (true)
            {
                if (Process.GetProcessesByName("BloonsTD6").Length > 0)
                {
                    Dispatcher.Invoke(() =>
                    {
                        runningStatus.Content = "BTD6 is running";
                        runningStatus.Foreground = new SolidColorBrush(Color.FromRgb(0, 255, 0));
                    });
                }
                else
                {
                    Dispatcher.Invoke(() =>
                    {
                        runningStatus.Content = "BTD6 is not running";
                        runningStatus.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
                    });
                }
                Thread.Sleep(2000);
            }
        }

        private void AddMod(string dll)
        {
            DockPanel dockPanel = new DockPanel
            {
                Margin = new Thickness(0, 5, 0, 0)
            };

            ModCheckBox modCheckBox = new ModCheckBox
            {
                RenderTransform = new ScaleTransform(1.5, 1.5),
                RenderTransformOrigin = new Point(0.5, 0.25),
                modDir = dll
            };
            modCheckBox.Click += ToggleMod;
            DockPanel.SetDock(modCheckBox, Dock.Left);
            dockPanel.Children.Add(modCheckBox);

            Label label = new Label
            {
                Content = Path.GetFileNameWithoutExtension(dll)
            };
            DockPanel.SetDock(label, Dock.Top);
            dockPanel.Children.Add(label);

            modList.Children.Add(dockPanel);
        }

        private void ToggleMod(object sender, RoutedEventArgs e)
        {
            try
            {
                ModCheckBox modCheckBox = (ModCheckBox)sender;
                if (Process.GetProcessesByName("BloonsTD6").Length > 0)
                {
                    using (Injector injector = new Injector(Process.GetProcessesByName("BloonsTD6")[0]))
                    {
                        injector.Inject(modCheckBox.modDir);
                    }
                }
                else
                {
                    MessageBox.Show("BTD6 is not running! Please start it.");
                    modCheckBox.IsChecked = !modCheckBox.IsChecked;
                }
            }
            catch (NullReferenceException nullRef)
            {
                MessageBox.Show("A Win32 error occurred when toggling the mod: " + nullRef.Message);
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred when toggling the mod: " + ex.Message);
            }
        }

        private void Import_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "BTD6 Mods (*.btd6mod)|*.btd6mod|All Files (*.*)|*.*"
            };

            if (openFileDialog.ShowDialog() == true)
            {
                try
                {
                    File.Copy(openFileDialog.FileName, btd6Path + @"\mods\" + Path.GetFileName(openFileDialog.FileName), true);
                    AddMod(btd6Path + @"\mods\" + Path.GetFileName(openFileDialog.FileName));
                }
                catch (Exception ex)
                {
                    MessageBox.Show("An error occurred when importing the mod: " + ex.Message);
                }
            }
        }

        private void Help_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Press \"Import Mod\" to import a btd6mod file.\n" +
                "Afterwards, a checkbox should pop up. This checkbox toggles the mod.\n" +
                "Please report all bugs to BowDown097 or Danny Parker on https://discord.gg/MmnUCWV in the #bug-reports channel.");
        }
    }
}