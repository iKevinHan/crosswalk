// Copyright (c) 2014 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/application/browser/tizen/tizen_cynara_checker.h"

#include <cynara-creds-socket.h>

#include "base/logging.h"

namespace xwalk {

TizenCynaraChecker::TizenCynaraChecker()
    : client_id_(NULL),
      user_id_(NULL),
      cynara_handler_(NULL) {
}

bool TizenCynaraChecker::Init(cynara* cynara_handler, int socket_fd) {
  LOG(ERROR) << "enter cynara check";

  if (cynara_handler == NULL)
    return false;
  else
    cynara_handler_ = cynara_handler;

  int ret;
  ret = cynara_creds_socket_get_client(socket_fd,
          CLIENT_METHOD_SMACK, &client_id_);
  if (ret != CYNARA_API_SUCCESS) {
    LOG(ERROR) << "cynara failed to get client id, error code " + ret;
    return false;
  }
  ret = cynara_creds_socket_get_user(socket_fd, USER_METHOD_UID, &user_id_);
  if (ret != CYNARA_API_SUCCESS) {
    LOG(ERROR) << "cynara failed to get user id, error code " + ret;
    return false;
  }

  return true;
}

int TizenCynaraChecker::CheckCynaraSync(const char* session,
        const char* privilege) {
  return cynara_check(cynara_handler_,
            client_id_, session, user_id_, privilege);
}

TizenCynaraChecker::~TizenCynaraChecker() {
  if (client_id_)
    free(client_id_);
  if (user_id_)
    free(user_id_);
}

}  // namespace xwalk
