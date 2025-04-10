#include "TreeNode.hh"
#include <sstream>
#include <string>

class Codec
{
private:
  void serializer_dfs_(TreeNode *root, std::string &code)
  {
    if (root == nullptr)
    {
      code += "# ";
      return;
    }

    code += std::to_string(root->val) + " ";
    serializer_dfs_(root->left, code);
    serializer_dfs_(root->right, code);
  }

  TreeNode *deserializer_dfs_(std::istringstream &stream)
  {
    std::string token{};
    if (stream >> token)
    {
      if (token == "#")
        return nullptr;

      TreeNode *node = new TreeNode(std::stoi(token));
      node->left     = deserializer_dfs_(stream);
      node->right    = deserializer_dfs_(stream);
      return node;
    }
    else
      return nullptr;
  }

public:
  std::string serialize(TreeNode *root)
  {
    std::string code{};
    serializer_dfs_(root, code);
    return code;
  }

  TreeNode *deserialize(std::string code)
  {
    auto iss = std::istringstream(code);
    return deserializer_dfs_(iss);
  }
};
