// search.cpp
//
// Created: 2023-04-14
// Author: (c) 2023 by C. Klukas
// License: MIT
// Description: Searches for text files that contain a specific search term and prints the file names to the console.
//
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

namespace fs = std::filesystem;

void toLower(std::vector<std::string>& vec) {
    for (auto& str : vec) {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
    }
}

std::string toLowerS(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
    return str;
}

void check_file(const std::filesystem::path path, const bool ignore_case, const bool use_and, const std::vector<std::string>& search_terms) {
    if (search_terms.empty())
    {
      std::cout << path.string() << '\n';
      return;
    }

    std::ifstream file(path);
    std::string line;
    bool has_all_search_terms = false;
    bool has_at_least_one_search_term = false;
    std::vector<std::string> search_terms_for_file = search_terms;
    
    while (std::getline(file, line))
    {
      if (ignore_case) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
      }
      for (auto it_st = search_terms_for_file.begin(); it_st != search_terms_for_file.end(); ) {
        if (line.find(*it_st) != std::string::npos) {
          has_at_least_one_search_term = true;
          if (!use_and) {
            goto end_read_file_by_line;
          }
          it_st = search_terms_for_file.erase(it_st);
        } else {
          ++it_st;
        }
      }
      if (search_terms_for_file.empty()) {
        has_all_search_terms = true;
        break;
      }
    }
    end_read_file_by_line:
    
    file.close();
    
    if ( (use_and && has_all_search_terms) || (!use_and && has_at_least_one_search_term) )
    {
      std::cout << path.string() << '\n';
    }
}

void find_files_with_extension_and_search_text(const std::string &path, const std::string &extension, 
      const bool ignore_case, const bool use_and, const std::vector<std::string>& search_terms)
{
  auto iter = fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied | fs::directory_options::follow_directory_symlink);
  auto end_iter = fs::end(iter);
  auto ec = std::error_code();
  for (; iter != end_iter; iter.increment(ec))
  {
    if (ec)
    {
        continue;
    }
    auto entry = *iter;
    if (entry.path().extension() != extension || !entry.is_regular_file())
      continue;
    
    check_file(entry.path(), ignore_case, use_and, search_terms);
  }
}

int main(int argc, char *argv[])
{
  if ( (argc < 2) || (strcmp(argv[1], "-h")==0) || (strcmp(argv[1], "--help")==0) )
  {
    std::cerr << "search - (c) 2023 by C. Klukas\n";
    std::cerr << "------------------------------\n";
    std::cerr << "Searches for text files that contain a specific search term and prints the file names to the console.\n";
    std::cerr << "Errors when traversing into a directory (e.g. access denied) are ignored.\n";
    std::cerr << "A call 'search /path/to/search .txt example' is similar to the Linux command 'grep -r --include \"*.txt\" \"example\" /path/to/search'.\n";
    std::cerr << "Multiple search terms can be specified.\n";
    std::cerr << "If -o is specified, a file is listed, if any search term is found (OR combination)\n";
    std::cerr << "If -i is specified, the search is case insensitive, this applies to the search terms and the provided file extension.\n";
    std::cerr << "If '-' is specified as search path, the files to be processed are read from stdin and the file extension parameter is not used/expected (second parameter is already a search term or '-i' or '-o').\n";
    std::cerr << "\n";
    std::cerr << "Usage (1): " << argv[0] << " <folder> <extension> [<search_term1>] [-i] [-o] [<search_term2>] [<search_term3>]...\n";
    std::cerr << "Usage (2): find ~ -type f -name \"*.txt\" | " << argv[0] << " - [<search_term1>] [-i] [-o] [<search_term2>] [<search_term3>]...\n";
    return 1;
  }

  const std::string path = argv[1];
  std::string extension = "";
  bool use_and = true;
  bool ignore_case = false;
  bool search_or_specified = false;
  std::vector<std::string> search_terms;
  int start_index = 3;
  if (path == "-") 
    start_index = 2;
  else
    extension = argv[2];
  
  for (int i = start_index; i < argc; ++i) {
      const auto& arg = argv[i];
      if (!search_or_specified && strcmp(arg, "-o")==0) {
          use_and = false;
          search_or_specified = true;
      }  else if (strcmp(arg, "-i")==0)
          ignore_case = true;
      else
        search_terms.push_back(argv[i]);
  }

  if (ignore_case) {
    toLower(search_terms);
    extension = toLowerS(extension);
  }
  
  if (path == "-") {
    std::string fn;
    while (std::getline(std::cin, fn))
      check_file(fn, ignore_case, use_and, search_terms);
  } else
    find_files_with_extension_and_search_text(path, extension, ignore_case, use_and, search_terms);
  
  return 0;
}
