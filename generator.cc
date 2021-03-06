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
HPCSoftware testing suite.

Date Created: Tue Dec  8 09:20:23 MST 2015

Author: Cormac Garvey

*/

#include "generator.h"


namespace hpcswtest {


Generator::Generator(std::string j_f_n): json_file_name_(j_f_n) {
  createTestObjects();
}


Generator::~Generator(void) {
  for (auto p: tests_) {
    delete p;
  }
}


void Generator::getCompilerJsonData(boost::property_tree::ptree::value_type pt, std::string &module_name, std::string &module_version, std::string &c_name, std::string &cpp_name, std::string &f_name, std::string &c_flags, std::string &cpp_flags, std::string &f_flags, std::string &c_link_libs, std::string &cpp_link_libs, std::string &f_link_libs) {
  module_name =  pt.second.get<std::string>("module_name");
  module_version =  pt.second.get<std::string>("module_version");
//  std::cout << "(Generator::Generator)" << pt.second.get<std::string>("module_name") << std::endl;
//  std::cout << "(Generator::Generator)" << pt.second.get<std::string>("module_version") << std::endl;
  c_name =  pt.second.get<std::string>("c_name");
  cpp_name =  pt.second.get<std::string>("cpp_name");
  f_name =  pt.second.get<std::string>("f_name");
  c_flags =  pt.second.get<std::string>("c_flags");
  cpp_flags =  pt.second.get<std::string>("cpp_flags");
  f_flags =  pt.second.get<std::string>("f_flags");
  c_link_libs =  pt.second.get<std::string>("c_link_libs");
  cpp_link_libs =  pt.second.get<std::string>("cpp_link_libs");
  f_link_libs =  pt.second.get<std::string>("f_link_libs");
}


void Generator::getModuleNameVersionJsonData(boost::property_tree::ptree::value_type pt, std::string &module_name, std::string &module_version) {
  module_name =  pt.second.get<std::string>("module_name");
  module_version =  pt.second.get<std::string>("module_version");
}


void Generator::getRunScriptJsonData(boost::property_tree::ptree::value_type pt, std::string &run_script) {
  run_script =  pt.second.get<std::string>("run_script");
}


void Generator::getExtraModJsonData(boost::property_tree::ptree::value_type pt, int extra_module_num, std::string &extra_module_name, std::string &extra_module_version) {
  extra_module_name =  pt.second.get<std::string>("extra_module_name" + std::to_string(extra_module_num));
  extra_module_version =  pt.second.get<std::string>("extra_module_version" + std::to_string(extra_module_num));
//  if (extra_module_name == "none") {
//    extra_module_name = "";
//  }
  if (extra_module_name != "none" && extra_module_version == "none") {
    extra_module_version = "";
  }
}


void Generator::getExeExeArgsJsonData(boost::property_tree::ptree::value_type pt, std::string &exe_name, std::string &exe_args) {
  exe_name =  pt.second.get<std::string>("exe_name");
  exe_args =  pt.second.get<std::string>("exe_args");
  if (exe_args == "none") {
    exe_args = "";
  }
}


void Generator::getMpiCmdNameArgsJsonData(boost::property_tree::ptree::value_type pt, std::string &mpi_cmd_name, std::string &mpi_cmd_args) {
  mpi_cmd_name =  pt.second.get<std::string>("mpi_cmd_name");
  mpi_cmd_args =  pt.second.get<std::string>("mpi_cmd_args");
  if (mpi_cmd_name == "none") {
    mpi_cmd_name = "";
  }
  if (mpi_cmd_args == "none") {
    mpi_cmd_args = "";
  }
}


void Generator::getHeliosExesJsonData(boost::property_tree::ptree::value_type pt, std::string &aurora_exe_name, std::string &helios_exe_name, std::string &zenith_exe_name) {
  aurora_exe_name =  pt.second.get<std::string>("aurora_exe_name");
  helios_exe_name =  pt.second.get<std::string>("helios_exe_name");
  zenith_exe_name =  pt.second.get<std::string>("zenith_exe_name");
}


void Generator::getPythonModulesJsonData(boost::property_tree::ptree::value_type pt, std::vector<std::string> &python_modules) {
  std::string python_modules_str;
  std::string python_module;
  python_modules_str =  pt.second.get<std::string>("python_modules");
  if (python_modules_str != "none") {
    std::stringstream python_modules_ss(python_modules_str);
    while (python_modules_ss >> python_module) {
     python_modules.push_back(python_module);
    }
  }
}


void Generator::createTestObjects(void) {
  std::string module_name;
  std::string module_version;
  std::string c_name;
  std::string cpp_name;
  std::string f_name;
  std::string c_flags;
  std::string cpp_flags;
  std::string f_flags;
  std::string c_link_libs;
  std::string cpp_link_libs;
  std::string f_link_libs;
  std::string run_script;
  std::string extra_module_name1;
  std::string extra_module_version1;
  std::string extra_module_name2;
  std::string extra_module_version2;
  std::string exe_name;
  std::string exe_args;
  char * hpcswtest_queue_env;
  char * cpu_type_env;
  std::string hpcswtest_queue = "hpc_support";
  std::string cpu_type = "haswell";
//  std::cout << "(Enter Generator::Generator)" << std::endl;
  std::string cluster_name;
  boost::property_tree::ptree pt;
  if (hpcswtest_queue_env = std::getenv("HPCSWTEST_QUEUE")) {
     hpcswtest_queue = hpcswtest_queue_env;
  }
  if (cpu_type_env = std::getenv("HPCSWTEST_CPUTYPE")) {
     cpu_type = cpu_type_env;
  }
//  std::cout << "(Generator::Generator) json_file_name_ = " << json_file_name_ << std::endl;
  cluster_name = getClusterName();
//  std::cout << "(Generator::Generator) cluster_name = " << cluster_name << std::endl;
  boost::property_tree::read_json(json_file_name_, pt);
  for (auto v: pt.get_child(cluster_name)) {
//    std::cout << "(Generator::Generator) Test key= " << v.first << std::endl;
    for (auto v2: pt.get_child(cluster_name + "." + v.first)) {
      if (v.first == "compiler") {
        getCompilerJsonData(v2, module_name, module_version, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs);
        modules::modules_type modules;
        if (module_name != "none") {
          modules = {{module_name, module_version}};
        }
        jobscript::PbsScript pbs_script(modules,1, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
//        std::cout << "(generator) after pbs_script object generated" << std::endl;
        tests_.push_back(new hpcswtest::CompilerTest(pbs_script, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs));
//        std::cout << "(generator) after CompilerTest object generated" << std::endl;
//        tests_.push_back(std::unique_ptr<hpcswtest::HpcSwTest> (new hpcswtest::CompilerTest(pbs_script, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs)));
      } else if (v.first == "mcnp") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        getExtraModJsonData(v2, 2, extra_module_name2, extra_module_version2);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{extra_module_name2,extra_module_version2},{module_name, module_version}});
        removeNoneModules(modules);
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::McnpTest(pbs_script, run_script));
      } else if (v.first == "mcnpx") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        getExtraModJsonData(v2, 2, extra_module_name2, extra_module_version2);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{extra_module_name2,extra_module_version2},{module_name, module_version}});
        removeNoneModules(modules);
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::McnpxTest(pbs_script, run_script));
      } else if (v.first == "mpi") {
        std::string mpi_cmd_name;
        std::string mpi_cmd_args;
        getCompilerJsonData(v2, module_name, module_version, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs);
        getMpiCmdNameArgsJsonData(v2, mpi_cmd_name, mpi_cmd_args);
        modules::modules_type modules({{module_name, module_version}});
        jobscript::PbsScript pbs_script(modules, 2, 1, mpi_cmd_name, mpi_cmd_args, "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::MpiTest(pbs_script, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs));
      } else if (v.first == "blas") {
        getCompilerJsonData(v2, module_name, module_version, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs);
        modules::modules_type modules({{module_name, module_version}});
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::BlasTest(pbs_script, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs));
      } else if (v.first == "boost") {
        getCompilerJsonData(v2, module_name, module_version, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs);
        modules::modules_type modules({{module_name, module_version}});
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::BoostTest(pbs_script, c_name, cpp_name, f_name, c_flags, cpp_flags, f_flags, c_link_libs, cpp_link_libs, f_link_libs));
      } else if (v.first == "scale") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
        getExeExeArgsJsonData(v2, exe_name, exe_args);
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", exe_name, exe_args, "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::ScaleTest(pbs_script, v.first));
      } else if (v.first == "scale62") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
        getExeExeArgsJsonData(v2, exe_name, exe_args);
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", exe_name, exe_args, "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::Scale62Test(pbs_script, v.first));
      } else if (v.first == "serpent") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 4, 2, "", "", "", "", "", "", hpcswtest_queue, cpu_type, "0:05:00");
        tests_.push_back(new hpcswtest::SerpentTest(pbs_script, run_script));
      } else if (v.first == "cth") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::CthTest(pbs_script, run_script));
      } else if (v.first == "helios") {
        std::string aurora_exe_name;
        std::string helios_exe_name;
        std::string zenith_exe_name;
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
//        getExeExeArgsJsonData(v2, exe_name, exe_args);
        getHeliosExesJsonData(v2, aurora_exe_name, helios_exe_name, zenith_exe_name);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::HeliosTest(pbs_script, aurora_exe_name, helios_exe_name, zenith_exe_name, v.first));
      } else if (v.first == "helioslint64") {
        std::string aurora_exe_name;
        std::string helios_exe_name;
        std::string zenith_exe_name;
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
//        getExeExeArgsJsonData(v2, exe_name, exe_args);
        getHeliosExesJsonData(v2, aurora_exe_name, helios_exe_name, zenith_exe_name);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::HeliosLinT64Test(pbs_script, aurora_exe_name, helios_exe_name, zenith_exe_name, v.first));
      } else if (v.first == "mc21") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
        removeNoneModules(modules);
//        getExeExeArgsJsonData(v2, exe_name, exe_args);
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 12, 12, "", "", "", "", "", "", hpcswtest_queue, cpu_type, "0:10:00");
        tests_.push_back(new hpcswtest::Mc21Test(pbs_script, run_script));
//        static_cast<hpcswtest::Mc21Test *>(tests_[tests_.size()-1])->setTestNumber(tests_[tests_.size()-1]->getTestObjectCount());  
//        tests_[tests_.size()-1]->setTestNumber(tests_[tests_.size()-1]->getTestObjectCount());  
      } else if (v.first == "vasp") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
        removeNoneModules(modules);
//        getExeExeArgsJsonData(v2, exe_name, exe_args);
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::VaspTest(pbs_script, run_script));
//        static_cast<hpcswtest::VaspTest *>(tests_[tests_.size()-1])->setTestNumber(tests_[tests_.size()-1]->getTestObjectCount());  
//        tests_[tests_.size()-1]->setTestNumber(tests_[tests_.size()-1]->getTestObjectCount());  
      } else if (v.first == "gaussian") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        getExtraModJsonData(v2, 1, extra_module_name1, extra_module_version1);
        getRunScriptJsonData(v2, run_script);
        modules::modules_type modules({{extra_module_name1,extra_module_version1},{module_name, module_version}});
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::GaussianTest(pbs_script, run_script));
      } else if (v.first == "abaqus") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        modules::modules_type modules({{module_name, module_version}});
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::AbaqusTest(pbs_script, run_script));
      } else if (v.first == "starccm") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        modules::modules_type modules({{module_name, module_version}});
        getRunScriptJsonData(v2, run_script);
        jobscript::PbsScript pbs_script(modules, 2, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::StarccmTest(pbs_script, run_script));
      } else if (v.first == "matlab") {
        getModuleNameVersionJsonData(v2, module_name, module_version);
        modules::modules_type modules({{module_name, module_version}});
        getExeExeArgsJsonData(v2, exe_name, exe_args);
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", exe_name, exe_args, "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::MatlabTest(pbs_script));
      } else if (v.first == "python2") {
        std::vector<std::string> python_modules;
        getModuleNameVersionJsonData(v2, module_name, module_version);
        modules::modules_type modules({{module_name, module_version}});
        getPythonModulesJsonData(v2, python_modules);
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::Python2Test(pbs_script, python_modules, v.first));
      } else if (v.first == "python3") {
        std::vector<std::string> python_modules;
        getModuleNameVersionJsonData(v2, module_name, module_version);
        modules::modules_type modules({{module_name, module_version}});
        getPythonModulesJsonData(v2, python_modules);
        jobscript::PbsScript pbs_script(modules, 1, 1, "", "", "", "", "", "", hpcswtest_queue, cpu_type);
        tests_.push_back(new hpcswtest::Python3Test(pbs_script, python_modules, v.first));
      } else {
          std::cerr << "Error: Do not recognize this test " << v.first << " (" << __FILE__ << "," << __LINE__ << ")" << std::endl;
          exit(EXIT_FAILURE);
      }
    }
  }
}


void Generator::runTests(void) {
  for (auto t: tests_) {
    t->runTest();
  }
}


} // namespace hpcswtest

