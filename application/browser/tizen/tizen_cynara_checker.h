// Copyright (c) 2014 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_APPLICATION_BROWSER_TIZEN_TIZEN_CYNARA_CHECKER_H_
#define XWALK_APPLICATION_BROWSER_TIZEN_TIZEN_CYNARA_CHECKER_H_

#include <cynara-client.h>

namespace xwalk {

// Helper Class to check cynara
class TizenCynaraChecker {
 public:
  TizenCynaraChecker();
  virtual ~TizenCynaraChecker();

  // Cynara needs the socket file descriptor, through which BP is communicating
  // with RP, to indentify the correspondent RP.
  bool Init(cynara* cynara_handler, int socket_fd);

  // The parameter session is not used currently.
  int CheckCynaraSync(const char* session, const char* privilege);

 private:
  // This class is resposible to free memory
  char* client_id_;
  char* user_id_;

  cynara* cynara_handler_;
};

}  // namespace xwalk

#endif  // XWALK_APPLICATION_BROWSER_TIZEN_TIZEN_CYNARA_CHECKER_H_
