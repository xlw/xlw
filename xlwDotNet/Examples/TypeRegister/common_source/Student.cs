namespace TypeRegDemo
{
    public class Student
    {
        private readonly string _name;
        private readonly double _age;

        public Student(string Name, double Age)
        {
            _name = Name;
            _age = Age;
        }

        public string Name
        {
            get { return _name; }
        }

        public double Age
        {
            get { return _age; }
        }

        public double ExamResult
        {
            get { return _age * 0.7; }
        }
    }
}
