using System;

namespace xlwDotNet
{
    [AttributeUsage(AttributeTargets.Method)]
    public sealed class ExcelOnOpenAttribute : Attribute
    {
    }

    [AttributeUsage(AttributeTargets.Method)]
    public sealed class ExcelOnCloseAttribute : Attribute
    {
    }
}
