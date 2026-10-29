using System;

namespace xlwDotNet
{
    [AttributeUsage(AttributeTargets.Method)]
    public sealed class ExcelExportAttribute : Attribute
    {
        public string Description { get; set; }
        public bool volatileFlag { get; set; }
        public bool timeFlag { get; set; }
        public bool threadSafeFlag { get; set; }
        public bool xlmCommandFlag { get; set; }

        public ExcelExportAttribute(string description)
        {
            Description = description;
        }

        public ExcelExportAttribute(string description, bool volatileFlag)
        {
            Description = description;
            this.volatileFlag = volatileFlag;
        }

        public ExcelExportAttribute(string description, bool volatileFlag, bool timeFlag)
        {
            Description = description;
            this.volatileFlag = volatileFlag;
            this.timeFlag = timeFlag;
        }

        public ExcelExportAttribute(string description, bool volatileFlag, bool timeFlag, bool threadSafeFlag)
        {
            Description = description;
            this.volatileFlag = volatileFlag;
            this.timeFlag = timeFlag;
            this.threadSafeFlag = threadSafeFlag;
        }
    }
}
