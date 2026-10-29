using System;

namespace xlwDotNet
{
    [AttributeUsage(AttributeTargets.Parameter)]
    public sealed class ParameterAttribute : Attribute
    {
        public string Description { get; }

        public ParameterAttribute(string description)
        {
            Description = description;
        }
    }
}
