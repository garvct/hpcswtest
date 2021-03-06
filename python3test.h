/*

Copyright 2017 Battelle Energy Alliance, LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Description
-----------
HPC Software test suite.
Python3Test is a subclass of base class Python2Test.

Date Created: Wed Dec 23 11:38:37 MST 2015

Author: Cormac Garvey

*/

#ifndef HPCSWTEST_PYTHON3TEST_H_
#define HPCSWTEST_PYTHON3TEST_H_

#include "python2test.h"
#include "helper.h"

#include <fstream>


namespace hpcswtest {


class Python3Test: public Python2Test {

  public:
    Python3Test(const jobscript::PbsScript &, const std::vector<std::string> &, const std::string &);
    virtual ~Python3Test(void) {};
    virtual void runTest(void) override;

  private:
    std::string log_file_name_;
    std::string result_file_name_;
    std::ofstream flog_;
    std::ofstream fresult_;
    const static std::vector<std::string> python3_inputs_;

}; // class Python3Test


} // namespace hpcswtest

#endif  // HPCSWTEST_PYTHON3TEST_H
