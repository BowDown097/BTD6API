using Microsoft.Win32;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace BTD6APIInjector
{
    /// <summary>
    /// Methods relating to Steam and Steam game info. Made by Danny Boi
    /// </summary>
    public class SteamUtils
    {
        /// <summary>
        /// For processing strings so they are in the correct format for this class
        /// </summary>
        private class Utils
        {
            // Takes any quotation marks out of a string.
            public static string StripQuotes(string str)
            {
                return str.Replace("\"", "");
            }

            // Convert Unix path to Windows path
            public static string UnixToWindowsPath(string UnixPath)
            {
                return UnixPath.Replace("/", "\\").Replace("\\\\", "\\");
            }
        }

        /// <summary>
        /// Use the steam game's app ID to check if the game is installed
        /// </summary>
        /// <param name="appid">Steam game's app ID</param>
        /// <returns>true or false, whether or not the game is installed</returns>
        public static bool IsGameInstalled(ulong appid)
        {
            return (int)Registry.GetValue(Registry.CurrentUser +
                "\\Software\\Valve\\Steam\\Apps\\" + appid, "Installed", null) == 1;
        }

        /// <summary>
        /// Get steam directory from registry
        /// </summary>
        /// <returns>returns steam directory or null</returns>
        public static string GetSteamDir()
        {
            return Utils.UnixToWindowsPath(Registry.GetValue(Registry.CurrentUser +
"\\Software\\Valve\\Steam", "SteamPath", null).ToString());
        }

        public static string GetGameDataDir(ulong appid, string userid = "")
        {
            string steamDir = GetSteamDir();
            if (!string.IsNullOrEmpty(steamDir))
            {
                if (IsGameInstalled(appid))
                {
                    if (string.IsNullOrEmpty(userid))
                    {
                        foreach (string user in Directory.EnumerateDirectories(steamDir + "\\userdata"))
                        {
                            if (Directory.Exists(user + "\\" + appid))
                            {
                                return user + "\\" + appid;
                            }
                        }
                    } // if userid is null (default), we will grab the first user in userdata that has the game
                    else
                    {
                        if (Directory.Exists($"{steamDir}\\userdata\\{userid}\\{appid}"))
                        {
                            return $"{steamDir}\\userdata\\{userid}\\{appid}";
                        }
                    } // if userid isn't null, we will search in the specified user directory in userdata
                }
            }

            return null;
        }

        /// <summary>
        /// Get game directory from steam app ID and game name
        /// </summary>
        /// <param name="appid">steam ID for the game you want the directory for</param>
        /// <param name="gameName">Name of the game you want the directory for</param>
        /// <returns>Game directory for game</returns>
        public static string GetGameDir(ulong appid, string gameName)
        {
            string steamDir = GetSteamDir();
            if (!string.IsNullOrEmpty(steamDir))
            {
                if (IsGameInstalled(appid))
                {
                    // Get game Directory...
                    List<string> SteamLibDirs = new List<string>
                    {
                        Utils.UnixToWindowsPath(steamDir) // This steam Directory is always here.
                    };
                    foreach (string configFile in File.ReadAllLines(steamDir + "\\steamapps\\libraryfolders.vdf"))
                    {
                        // To Example lines are
                        // 	"ContentStatsID"		"-4535501642230800231"
                        // "1"     "C:\\SteamLibrary"
                        // So, we scan for the items in quotes, if the first one is numeric, 
                        // then the second one will be a steam library.
                        MatchCollection matches = new Regex("\".*?\"").Matches(configFile);
                        for (int match = 0; match < matches.Count; match++)
                        {
                            if (match == 1)
                            {
                                SteamLibDirs.Add(Utils.UnixToWindowsPath(Utils.StripQuotes(matches[match].Value.ToString())));
                            }

                            if (match == 0)
                            {
                                if (!int.TryParse(Utils.StripQuotes(matches[match].Value.ToString()), out _))
                                {
                                    break;
                                }
                            }
                        }
                    }

                    for (int i = 0; i < SteamLibDirs.Count; i++)
                    {
                        string GameFolder = (SteamLibDirs[i] + "\\steamapps\\common\\" + gameName);
                        if (Directory.Exists(GameFolder))
                        {
                            return GameFolder;
                        }
                    }
                }
            }

            return null;
        }
    }
}
