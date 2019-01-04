using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewsGenerator
{
    public interface IMainFormInterface
    {
        void OutputWindow_WriteLine(string line, Color? color = null);
        void OutputWindow_WriteIndentedLine(string line, Color? color = null);
        void OutputWindow_WriteEmptyLine();
        string GetGeneratedFilesOutputFolder { get; }
        void EnableLoadDesktopDataButton();
        void EnableLoadViewDataButton();
    }
}
