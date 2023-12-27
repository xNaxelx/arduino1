#include <boost/asio/serial_port.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <string>
#include <boost/asio/streambuf.hpp>

int main()
{
    setlocale(LC_ALL, "Russian");

    //необходим для работы портов
    boost::asio::io_service m_ioService;
    
    //объект представляющий сом-порт
    boost::asio::serial_port m_port(m_ioService);
    //вывод в консоль
    std::cout << "Укажите название COM порта. Например \"COM1\"\n";
    //буффер для ввода
    std::string line;
    //считывание ввода
    std::getline(std::cin, line);
    // открывает указанный порт 
    m_port.open(line);

    m_port.set_option(boost::asio::serial_port_base::baud_rate(9600));
    m_port.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
    m_port.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
    m_port.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
    m_port.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));

    std::cout << "Управление светом:\n1 - включить\n2 - выключить\n";

    while (true) {
        //Чтение и отправка команды
        std::string s;
        std::cin >> s;
        boost::asio::streambuf b;
        std::ostream os(&b);
        os << s;
        boost::asio::write(m_port, b.data());
        //Чтение ответа
        char bytes[1024];
        m_port.read_some(boost::asio::buffer(&bytes, sizeof(char) * 1024));
        std::cout << std::string(bytes) << std::endl;
    }
}