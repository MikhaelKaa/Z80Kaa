// See https://aka.ms/new-console-template for more information
using System.IO.Ports;

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
    "COM9",
    115200,
    System.IO.Ports.Parity.None,
    8,
    System.IO.Ports.StopBits.One);


if (port.IsOpen == true)
    port.Close();

port.Open();

while (true)
{
    SetCmd();
    //Console.WriteLine("loop");
    Thread.Sleep(100);
}

//  Отправка команды управления
int SetCmd()
{
    byte[] data = new byte[1];
    data[0] = 0x72;// 'r';    
    //data[0] = 0x6d;// 'm';    

    port.Write(data, 0, 1);
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