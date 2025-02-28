#pragma once

#include <mutex>
#include <map>
#include <string>
#include <memory>

#include "ftp_user.h"
#include <fineftp/permissions.h>

namespace fineftp
{
  class UserDatabase
  {
  public:
    UserDatabase(std::ostream& output, std::ostream& error);

    bool addUser(const std::string& username, const std::string& password, const std::string& local_root_path, Permission permissions);

    std::shared_ptr<FtpUser> getUser(const std::string& username, const std::string& password) const;

  private:
    bool isUsernameAnonymousUser(const std::string& username) const;

    mutable std::mutex                              database_mutex_;
    std::map<std::string, std::shared_ptr<FtpUser>> database_;
    std::shared_ptr<FtpUser>                        anonymous_user_;

    std::ostream& output_;  /* Normal output log */
    std::ostream& error_;   /* Error output log */
  };
}