#include <boost/spirit/home/x3.hpp>
#include <fstream>
#include <iostream>

#include <gh/issues.hxx>

#include <boost/process.hpp>



int main(int argc, char** argv) {

  std::string adoc = argv[1];
  std::string gh_api_endpoint = (argc > 2) ? argv[2] : "https://api.github.com";

  gh::auth auth{ 
    std::getenv("GH_USER"),
    std::getenv("GH_PASS")
  };

  std::ifstream ifs{adoc};

  for (std::string line; std::getline(ifs, line); ) {

    using namespace boost::spirit;
    using x3::phrase_parse;
    using x3::ascii::space;


    std::string owner;
    auto set_owner = [&](auto& ctx){ owner = _attr(ctx);  };

    std::string repo;
    auto set_repo = [&](auto& ctx){ repo = _attr(ctx); };

    uint64_t issue = 0;
    auto set_issue = [&](auto& ctx){ issue = _attr(ctx); };


    std::string::const_iterator first = line.begin();
    std::string::const_iterator last = line.end();
    bool r = phrase_parse( first, last,
      "include::" >> 
       (+(x3::char_ - "/"))[set_owner] >> "/" >> (+(x3::char_ - "#"))[set_repo]
       >> "#" >> x3::ulong_long[set_issue]
       >> "[" >> *(x3::char_ - "]") >> "]",
      space
    );

    if ( (r) && (first == last) ) {
      gh::get_issue(owner, repo, issue, [](gh::repos::issue_t&& issue) {

        namespace bp = boost::process;
        bp::opstream in;
        bp::ipstream out;
        bp::child c("./convert-markdown-to-asciidoc", bp::std_out > out, bp::std_in < in);

        in << "### " << issue.title << "( #" << issue.number << " )\n\n";
        in << "_Discussion and History on Github : [#" << issue.number << "](" << issue.html_url << ")._\n\n";
        in << issue.body << std::endl;

        in.pipe().close();
        c.wait();

        std::cout << "\n";
        std::cout << out.rdbuf();
        std::cout << "\n";

      }, auth, gh_api_endpoint);

    } else {
      std::cout << line << "\n";
    }

  }

  return 0;
}
