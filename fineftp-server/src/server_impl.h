#pragma once

#include <vector>
#include <thread>
#include <atomic>

#include <asio.hpp>

#include <ftp_session.h>

#include <ftp_user.h>
#include <user_database.h>

namespace fineftp
{
  class FtpServerImpl
  {
  public:
    FtpServerImpl(uint16_t port);
    FtpServerImpl(const std::string& address, uint16_t port);

    ~FtpServerImpl();

    bool addUser(const std::string& username, const std::string& password, const std::string& local_root_path, const Permission permissions);
    bool addUserAnonymous(const std::string& local_root_path, const Permission permissions);

    bool start(size_t thread_count = 1);

    void stop();

    int getOpenConnectionCount();

    uint16_t getPort() const; 
    std::string getAddress() const;

  private:
    void acceptFtpSession(std::shared_ptr<FtpSession> ftp_session, asio::error_code const& error);

    asio::ip::tcp::endpoint getEndpoint();

  private:
    UserDatabase   ftp_users_;

    const uint16_t port_;
    const std::string& address_;
    const std::string no_address_ = "NO_ADDRESS";

    std::vector<std::thread> thread_pool_;
    asio::io_service         io_service_;
    asio::ip::tcp::acceptor  acceptor_;

    std::atomic<int> open_connection_count_;
  };
}