using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Cache;
using System.Reflection;
using System.Text;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

namespace Statman.Util
{
    class UpdateChecker
    {
        [DataContract]
        private class Release
        {
            [DataMember(Name = "html_url")]
            public string HTMLUrl { get; set; }

            [DataMember(Name = "tag_name")]
            public string TagName { get; set; }

            [DataMember(Name = "prerelease")]
            public bool PreRelease { get; set; }
        }

        public static bool HasNewerVersion(out string p_CurrentVersion, out string p_Version, out string p_ReleaseURL, out bool p_PreRelease)
        {
            var s_Assembly = Assembly.GetExecutingAssembly();
            var s_VersionInfo = FileVersionInfo.GetVersionInfo(s_Assembly.Location);
            p_CurrentVersion = s_VersionInfo.FileVersion.Trim();

            p_Version = p_CurrentVersion;
            p_ReleaseURL = null;
            p_PreRelease = false;

            var s_ReleaseData = GetLatestReleaseData();

            if (string.IsNullOrWhiteSpace(s_ReleaseData))
                return false;

            string s_LatestVersionString;
            if (!ParseReleaseData(s_ReleaseData, out s_LatestVersionString, out p_ReleaseURL, out p_PreRelease))
                return false;

            try
            {
                var s_CurrentVersion = new Version(p_CurrentVersion);
                var s_LatestVersion = new Version(s_LatestVersionString);

                p_Version = s_LatestVersionString;

                return s_LatestVersion.CompareTo(s_CurrentVersion) > 0;
            }
            catch (Exception)
            {
                return false;
            }
        }

        private static bool ParseReleaseData(string p_Data, out string p_LatestVersion, out string p_ReleaseURL, out bool p_PreRelease)
        {
            p_LatestVersion = p_ReleaseURL = null;
            p_PreRelease = false;

            try
            {
                using (var s_Stream = new MemoryStream(Encoding.UTF8.GetBytes(p_Data)))
                {
                    var s_Serializer = new DataContractJsonSerializer(typeof (Release));
                    var s_Release = s_Serializer.ReadObject(s_Stream) as Release;

                    if (s_Release == null || string.IsNullOrWhiteSpace(s_Release.TagName))
                        return false;

                    p_LatestVersion = s_Release.TagName.TrimStart('v').Trim();
                    p_ReleaseURL = s_Release.HTMLUrl;
                    p_PreRelease = s_Release.PreRelease;

                    return true;
                }
            }
            catch (Exception)
            {
                return false;
            }
        }

        private static string GetLatestReleaseData()
        {
            var s_Request = (HttpWebRequest) WebRequest.Create("https://api.github.com/repos/OrfeasZ/Statman/releases/latest");
            s_Request.Method = "GET";

            s_Request.UserAgent = "Statman-Updater";
            s_Request.Timeout = 5000;
            s_Request.CachePolicy = new RequestCachePolicy(RequestCacheLevel.BypassCache);

            string s_Output;

            try
            {
                using (var s_Response = s_Request.GetResponse())
                    using (var s_Stream = new StreamReader(s_Response.GetResponseStream(), Encoding.GetEncoding(1252)))
                        s_Output = s_Stream.ReadToEnd();
            }
            catch (Exception)
            {
                return null;
            }

            return s_Output;
        }
    }
}
