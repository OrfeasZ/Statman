using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Statman.Util
{
    internal class HM3Options
    {
        public bool Cheats { get; set; } = false;
        public bool UnlimitedSaves { get; set; } = false;
        public bool Hitman2016Mode { get; set; } = false;
        public bool Hitman2016DebugMode { get; set; } = false;
        public bool Overlay { get; set; } = true;
    }

    internal class StatmanOptions
    {
        public bool DarkMode { get; set; } = false;
        public HM3Options HM3 { get; set; } = new HM3Options();
    }

    class Options
    {
        private static string m_OptionsPath;
        private static StatmanOptions m_Options;

        static Options()
        {
            m_OptionsPath = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "statman.json");
            m_Options = ParseOptions();
        }

        private static StatmanOptions ParseOptions() 
        {
            try
            {
                if (File.Exists(m_OptionsPath))
                {
                    var s_Json = File.ReadAllText(m_OptionsPath);
                    return JsonConvert.DeserializeObject<StatmanOptions>(s_Json);
                }
            }
            catch (Exception) 
            {
                return new StatmanOptions();
            }

            return new StatmanOptions();
        }

        private static void WriteOptions()
        {
            try
            {
                var s_Json = JsonConvert.SerializeObject(m_Options, Formatting.Indented);
                File.WriteAllText(m_OptionsPath, s_Json);
            }
            catch (Exception)
            {
                // No-op.
            }
        }

        public static StatmanOptions Get() { return m_Options; }

        public static void Update(Action<StatmanOptions> updater)
        {
            lock (m_Options)
            {
                updater(m_Options);
                WriteOptions();
            }
        }
    }
}
