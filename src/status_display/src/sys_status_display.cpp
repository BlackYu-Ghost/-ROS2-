#include <QApplication>
#include <QLabel>
#include <QString>
#include<rclcpp/rclcpp.hpp>
#include "status_interfaces/msg/system_status.hpp"

using SystemStatus = status_interfaces::msg::SystemStatus;

class SystemStatusDisplay : public rclcpp::Node {
private:
    rclcpp::Subscription<SystemStatus>::SharedPtr subscription_;
    QLabel *label_;
public:
    SystemStatusDisplay() : Node("system_status_display") { 
        label_ = new QLabel();
        subscription_ = this->create_subscription<SystemStatus>(
            "system_status", 10, std::bind(&SystemStatusDisplay::statusCallback, this, std::placeholders::_1));
        label_->setText(get_qstr_from_msg(std::make_shared<SystemStatus>()));
        label_->show();
    }
    void statusCallback(const SystemStatus::SharedPtr msg) {
        label_->setText(get_qstr_from_msg(msg));
    }       
    QString get_qstr_from_msg(const SystemStatus::SharedPtr msg){
        std::stringstream show_str;

        show_str <<"========= System Status =========\n"
        <<"Time " << msg->stamp.sec << "\ts\n"
        <<"Host Name: " << msg->host_name << "\n"
        <<"CPU Usage: " << msg->cpu_percent << "\t%\n"
        <<"Memory Usage: " << msg->memory_percent << "\t%\n"
        <<"Memory Total: " << msg->memory_total << "\tMB\n"
        <<"Memory Available: " << msg->memory_available << "\tMB\n"
        <<"Network Sent: " << msg->net_sent << "\tMB\n"
        <<"Network Received: " << msg->net_recv << "\tMB\n"
        <<"==================================\n";

        return QString::fromStdString(show_str.str());
    }
};

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);
    auto node = std::make_shared<SystemStatusDisplay>();
    std::thread spin_thread([&](){
        rclcpp::spin(node);
    });
    spin_thread.detach();
    app.exec();
    return 0;

}