using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;
namespace WyScInterfaceLib
{
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    [Guid("3191B991-DC97-4842-BB94-0B58BE591507")]
    public interface IWyScHook
    {
        [DispId(1)]
        bool beforeSend(ref int hr,ref string inputData,ref string outputData);
        [DispId(2)]
        void afterSend(ref int hr,ref string outputData);
    }

    [ClassInterface(ClassInterfaceType.None)]
    [Guid("94FD71D5-6D8A-45A6-A369-51C4DDAC907F")]
    public class WyScInterFaceComLib:IWyScHook
    {
        public bool beforeSend(ref int hr, ref string inputData,ref string outputData)
        {
            MessageBox.Show(inputData, "传入参数", MessageBoxButtons.OKCancel);
            inputData += "$$$$$$$$$change in Data";
            outputData = "wangyong prograssed";
            return true;
        }
        public void afterSend(ref int hr,ref string outputData)
        {
            //return 0;
        }
    }
}
