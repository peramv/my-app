using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ViewsGenerator
{
    class NumericTextBox : TextBox
    {
        const int ES_NUMBER = 0x2000;
        const int WM_PASTE = 0x0302;
        const string NumberTemplate = @"^\d+$";

        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams parameters = base.CreateParams;
                parameters.Style |= ES_NUMBER;

                return parameters;
            }
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_PASTE)
            {
                string data = Clipboard.GetDataObject().GetData(DataFormats.Text) as string;
                if (!Regex.IsMatch(data, NumberTemplate))
                {
                    return;
                }
            }

            base.WndProc(ref m);
        }
    }
}
