using System;
using System.IO.Ports;

class ProgPC
{
    static SerialPort port;
    internal enum Prog_cmd : int
    {
        version = 0,
        answer,
        read,
        write,
        erase_all,
        cpu_suspend,
        cpu_resume,
        cpu_reset,
        cpu_start,
        reset_low,
        reset_high,
        dbg_print,
    };

    static byte[] temrorary_buf = new byte[64];
    static void Main(string[] args)
    {
        string file_name;
        string port_name;
        // Аргументы.
        Console.WriteLine(args.Length);
        if(args.Length == 2)
        {
            port_name = args[0];
            file_name = args[1];
        } else
        {
            Console.WriteLine("Имя файла с данными для записи по умолчанию test.bin");
            file_name = "C:\\Users\\Kaa\\Documents\\Speccy\\Z80Kaa\\FW\\out.bin";
            Console.WriteLine("Имя порта по умолчанию COM9");
            port_name = "COM9";
        }

        FileStream stream = new FileStream(file_name, FileMode.Open, FileAccess.Read);
        byte[] file_bytes = new byte[0x8000];
        stream.Read(file_bytes, 0, 0x8000);

        port = new SerialPort(
            port_name,
            115200,
            Parity.None,
            8,
            StopBits.One);


        if (port.IsOpen == true)
            port.Close();

        port.Open();



        while (true)
        {
            Console.WriteLine("send cmd version");
            SendCmd((int)Prog_cmd.version);
            Thread.Sleep(100);

            Console.WriteLine("send cmd cpu suspend");
            SendCmd((int)Prog_cmd.cpu_suspend);
            Thread.Sleep(100);

            Console.WriteLine("send 64*512 bytes");
            for (int i = 0; i < 512; i++)
            {
                for(int j = 0; j < 64; j++)
                {
                    temrorary_buf[j] = file_bytes[i*64 + j];
                }
                SendData(temrorary_buf);
                Console.WriteLine("send cmd write adr {0}" , i * 64);
                SendCmd((int)Prog_cmd.write, i * 64);
            }

            Console.WriteLine("send cmd cpu start");
            SendCmd((int)Prog_cmd.cpu_start);

            Thread.Sleep(300);
            port.Close();
            Environment.Exit(0);
        }

    }


    //  Отправка команды управления
    static int SendCmd(int cmd, int adr = 0)
    {
        string answer_str = port.ReadExisting();
        byte[] data = new byte[8];
        data[0] = 0x55; // header
        data[1] = (byte)cmd;
        data[2] = (byte)(adr >> 0);
        data[3] = (byte)(adr >> 8);
        data[4] = 0x00; // 
        data[5] = 0x00; // 
        data[6] = 0x00; // 
        data[7] = 0x00; // 

        port.Write(data, 0, 8);


        int bytes_cnt = port.BytesToRead;
        if (bytes_cnt > 0)
        {
            byte[] answer = new byte[(int)port.BytesToRead];
            answer_str = port.ReadExisting();
            string text = System.Text.Encoding.UTF8.GetString(answer, 2, 4);

            return 0;
        }

        return -1;
    }

    // Отпрравка массива данных.
    static void SendData(byte[] buf)
    {
        port.Write(buf, 0, buf.Length);
    }
}
