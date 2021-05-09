#include <iostream>
#include <fstream>
#include <sstream>
#include <cmark.h>
#include <node.h>
#include <regex>
#include "metadata.h"


int main(int argc, const char * argv[]) {
    cmark_node* document = nullptr;
    
    std::ifstream inputStream;
    std::stringstream buffer;
    
    inputStream.open("Test.md");
    buffer << inputStream.rdbuf();
    std::string fileContents = buffer.str();
    
    std::cout << "The buffer as read from the input file:" << std::endl;
    std::cout << fileContents << std::endl;
    
    document = cmark_parse_document(fileContents.c_str(), fileContents.length(), CMARK_OPT_DEFAULT);
    
//    std::cout << "the root node type is " << document->type << std::endl;
    
    cmark_event_type ev_type;
    cmark_iter *iter = cmark_iter_new(document);
    
    while ((ev_type = cmark_iter_next(iter)) != CMARK_EVENT_DONE) {
        cmark_node *cur = cmark_iter_get_node(iter);
            // Do something with `cur` and `ev_type`
        //std::cout << cur->type << std::endl;
        if (cur->type == CMARK_NODE_CODE_BLOCK)
        {
            std::cout << "encountered code block" << std::endl;
            bool isnull = cur-> data == NULL;
            // std::cout << "the nodes data pointer is " <<  isnull << std::endl;
            // std::cout << "the node's length is " << cur->len << std::endl;
            
            Metadata metadata((const char*)cur->data, cur->len);
            
            if (metadata.getIsValid())
            {
                std::cout << "metadata friendly name is: " << metadata.getFriendlyName() << std::endl;
                std::cout << "metadata pub date is: " << metadata.getPublishDate() << std::endl;
                cmark_node_unlink(cur);
                cmark_node_free(cur);
            }
        }
    }
    
    cmark_iter_free(iter);
    
    std::cout << "The buffer after it was processed and converted to HTML:" << std::endl;
    std::cout << cmark_render_html(document, CMARK_OPT_DEFAULT) << std::endl;

    return 0;
}
