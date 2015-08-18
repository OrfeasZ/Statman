namespace Statman.Network
{
    public class PipeMessage
    {
        public string Module 
        { 
            get { return m_Module; } 
            set
            {
                if (string.IsNullOrEmpty(value))
                    m_Module = "__";
                else if (value.Length == 1)
                    m_Module = value + "_";
                else
                    m_Module = value.Substring(0, 2);
            }
        }

        public string Type
        {
            get { return m_Type; }
            set
            {
                if (string.IsNullOrEmpty(value))
                    m_Type = "__";
                else if (value.Length == 1)
                    m_Type = value + "_";
                else
                    m_Type = value.Substring(0, 2);
            }
        }

        public string Content { get; set; }

        private string m_Module;
        private string m_Type;
    }
}
