#include <bits/stdc++.h>
#include <algorithm>
#include "huffman.h"
#include "rle.h"
#include "lzw.h"

using namespace std;

string ReadFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

void WriteStringIntoFile(const string& textfilename, const string& answer){
    string filename(textfilename);
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open()) {
        cout << "failed to open " << filename << '\n';
    } else {
        file_out << answer << endl;
        //cout << "Done Writing!" << endl;
    }
}

int main(){
    string filename("message.txt");
    string file_content;

    file_content = ReadFileIntoString(filename);
    //cout << file_content << endl;

    string huffman_encoded = HuffmanEncoding(file_content);
    WriteStringIntoFile("huffman_compressed.txt", huffman_encoded);
    cout << "Size of text when Huffman Encoded: " << huffman_encoded.size() <<"bits"<< endl;
    string best_technique = "Huffman Encoding";
    string ans = huffman_encoded;

    //Lempel-Ziv-Welch
    vector<int> lzw_encoded = LZW_encoding(file_content);
    std::ostringstream vts;
    if (!lzw_encoded.empty()){
        // Convert all but the last element to avoid a trailing ","
        std::copy(lzw_encoded.begin(), lzw_encoded.end()-1, std::ostream_iterator<int>(vts, " "));  
        // Now add the last element with no delimiter
        vts << lzw_encoded.back();
    }
    WriteStringIntoFile("lzw_compressed.txt", vts.str());
    int max_value_lzw = -1;
    for(int i = 0; i < lzw_encoded.size(); i++){
        if(max_value_lzw < lzw_encoded[i]) max_value_lzw = lzw_encoded[i];
    }
    //cout << endl << max_value_lzw << endl;
    int n_bits_each = log2(max_value_lzw);
    cout << "Size of text when LZW Encoded: " << (lzw_encoded.size()*(n_bits_each)) << "bits" << endl;
    if((lzw_encoded.size()*(n_bits_each)) < ans.size()){
        ans = vts.str();
        best_technique = "LZW Encoding";
    }

    string rl_encoded = RunLengthEncoding(file_content);
    WriteStringIntoFile("rle_compressed.txt", rl_encoded);
    cout << "Size of text when Run Length Encoded: " << (rl_encoded.size()*8) << "bits" << endl;
    if((rl_encoded.size()*8) < ans.size()){
        ans = rl_encoded;
        best_technique = "Run Length Encoding";
    }
    
    //cout << ans << endl;
    WriteStringIntoFile("compressed.txt", ans);
}