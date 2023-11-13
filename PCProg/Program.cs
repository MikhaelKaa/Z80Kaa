// See https://aka.ms/new-console-template for more information
using System.IO.Ports;

/*
enum commands
{
    nop = 0,
    read,
    write,
    cpu_suspend,
    cpu_resume,
    reset,
};*/

SerialPort port;
// получаем список доступных портов 
string[] ports = SerialPort.GetPortNames();



Console.WriteLine("Найдены следующие порты:");

// выводим список портов
for (int i = 0; i < ports.Length; i++)
{
    Console.WriteLine("[" + i.ToString() + "] " + ports[i].ToString());
}

port = new System.IO.Ports.SerialPort(
    "COM14",
    115200,
    System.IO.Ports.Parity.None,
    8,
    System.IO.Ports.StopBits.One);


if (port.IsOpen == true)
    port.Close();

port.Open();

while (true)
{
    Console.WriteLine("send cmd version");
    SendCmd(0x00);
    Thread.Sleep(100);

    Console.WriteLine("send 64 bytes");
    SendData();
    Thread.Sleep(100);

    Console.WriteLine("send cmd write");
    SendCmd(0x02);
    Thread.Sleep(100);

    Console.WriteLine("send cmd read");
    SendCmd(0x01);
    Thread.Sleep(100);
}



//  Отправка команды управления
int SendCmd(byte cmd)
{
    byte[] data = new byte[8];
    data[0] = 0x55; // header
    data[1] = cmd; // 
    data[2] = 0x00; // 
    data[3] = 0x00; // 
    data[4] = 0x00; // 
    data[5] = 0x00; // 
    data[6] = 0x00; // 
    data[7] = 0x00; // 


    port.Write(data, 0, 8);
    //  Отправляем запрос, ждем 100 мс и смотрим что пришло в ответ

    System.Threading.Thread.Sleep(1000);

    if (port.BytesToRead > 0)
    {
        byte[] answer = new byte[(int)port.BytesToRead];
        //Console.WriteLine(answer.ToString());
        //  Читаем буфер для анализа ответа на команду управления
        //port.Read(answer, 0, port.BytesToRead);
        //Console.WriteLine(answer.Length);
        Console.WriteLine(port.ReadExisting());
        return 0;
    }

    return -1;
    //  Если не пришло вообще никакого ответа,
    //   возвращаем отрицательное значение
}

void SendData()
{
    byte[] data = new byte[64];
    for(int i = 0; i < 64; i++)
    {
        data[i] = (byte)(i+0x30);
    }
    port.Write(data, 0, 64);

    System.Threading.Thread.Sleep(100);
}