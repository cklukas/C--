#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void find_files_with_extension_and_search_text(const std::string &path, const std::string &extension, const std::string &search_text)
{
  auto iter = fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied);
  auto end_iter = fs::end(iter);
  auto ec = std::error_code();
  for (; iter != end_iter; iter.increment(ec))
  {
    if (ec)
    {
        continue;
    }
    auto entry = *iter;
    if (!entry.is_regular_file() || entry.path().extension() != extension)
      continue;
    
    // if search_text is empty, print all files with the given extension
    if (search_text.empty())
    {
      std::cout << entry.path().string() << '\n';
      continue;
    }
    
    // otherwise, search for the search_text in the file and if found, print the file name
    std::ifstream file(entry.path());
    std::string line;
    while (std::getline(file, line))
    {
      if (line.find(search_text) != std::string::npos)
      {
        std::cout << entry.path().string() << '\n';
        break;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  if ((argc != 4) && (argc != 3))
  {
    std::cerr << "search - (c) 2023 by C. Klukas\n";
    std::cerr << "Searches for text files that contain a specific search term and prints the file names to the console.\n";
    std::cerr << "Errors, e.g. when reading a file or when traversing into a directory (e.g. access denied) are ignored.\n";
    std::cerr << "A call 'search /path/to/search .txt example' is similar to the Linux command 'grep -r --include \"*.txt\" \"example\" /path/to/search'.\n";
    std::cerr << "Usage: " << argv[0] << " <folder> <extension> [<search_text>]\n";
    return 1;
  }

  const std::string path = argv[1];
  const std::string extension = argv[2];
  // if argc == 3, search_text will be empty
  // set search_text to empty string if argc == 3
  std::string search_text;
  if (argc == 4) {
    search_text = argv[3];
  } else {
    search_text = "";
  }
  find_files_with_extension_and_search_text(path, extension, search_text);
}