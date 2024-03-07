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
        int start_adr = 0;
        int file_lenght  = 0x7fff;

        // Аргументы.
        Console.WriteLine(args.Length);

        switch (args.Length)
        {
            case 2:
                port_name = args[0];
                file_name = args[1];
                break;

            case 4:

                port_name = args[0];

                file_name = args[1];

                try
                {
                    start_adr = int.Parse(args[2]);
                    Console.WriteLine("Start adr = {0}", start_adr);
                    Thread.Sleep(1000);
                }
                catch (FormatException e)
                {
                    Console.WriteLine("Argument 2 error. Exit.");
                    Thread.Sleep(300);
                    Environment.Exit(0);
                }

                try
                {
                    file_lenght = int.Parse(args[3]);
                    Console.WriteLine("Lenght = {0}", file_lenght);
                    Thread.Sleep(1000);
                }
                catch (FormatException e)
                {
                    Console.WriteLine("Argument 3 error. Exit.");
                    Thread.Sleep(300);
                    Environment.Exit(0);
                }
                break;


            default:
                Console.WriteLine("Имя файла с данными для записи по умолчанию test.bin");
                //file_name = "C:\\Users\\Kaa\\Documents\\Speccy\\Z80Kaa\\FW\\out.bin";
                file_name = "C:\\Users\\Kaa\\Documents\\Speccy\\zs-pentagon\\FW\\out.bin";
                Console.WriteLine("Имя порта по умолчанию COM9");
                port_name = "COM9";
                Console.WriteLine("start_adr = 0");
                start_adr = 0;
                Console.WriteLine("file_lenght = 0x8000");
                file_lenght = 0x8000;
                break;
        }



        FileStream stream = new FileStream(file_name, FileMode.Open, FileAccess.Read);
        byte[] file_bytes = new byte[file_lenght];
        stream.Read(file_bytes, start_adr, file_lenght);

        port = new SerialPort(
            port_name,
            115200,
            Parity.None,
            8,
            StopBits.One);


        if (port.IsOpen == true)
            port.Close();

        try
        {
            port.Open();
        }
        catch (Exception)
        {
            Console.WriteLine("Cant open port. Exit");
            Thread.Sleep(300);
            Environment.Exit(0);
        }



        while (true)
        {
            Console.WriteLine("send cmd version");
            SendCmd((int)Prog_cmd.version);
            Thread.Sleep(100);

            Console.WriteLine("send cmd cpu suspend");
            SendCmd((int)Prog_cmd.cpu_suspend);
            Thread.Sleep(100);

            Console.WriteLine("send bytes {0}", file_lenght);
            Thread.Sleep(3000);
            for (int i = 0; i < file_lenght/64; i++)
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
