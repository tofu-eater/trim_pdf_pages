/*Dependencies

sudo apt-get install libpoppler-cpp-dev libboost-program-options-dev
sudo apt-get install libpodofo-dev
sudo apt-get install libqpdf-dev libboost-program-options-dev


Example run:
 g++ -std=c++11 -o pdf_trim pdf_trim.cpp -lqpdf
 ./pdf_trim input.pdf 28 40
Where the PDF to be targetted is called input.pdf, and keeps the pages 28 through


*/


#include <iostream>
#include <string>
#include <qpdf/QPDF.hh>
#include <qpdf/QPDFWriter.hh>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_pdf> <from_page> <to_page>" << std::endl;
        return 1;
    }

    std::string input_file(argv[1]);
    int from_page = std::stoi(argv[2]);
    int to_page = std::stoi(argv[3]);

    QPDF input_pdf;
    input_pdf.processFile(input_file.c_str());

    std::vector<QPDFObjectHandle> all_pages = input_pdf.getAllPages();
    const int num_pages = all_pages.size();
    if (from_page < 1 || to_page > num_pages || from_page > to_page) {
        std::cerr << "Invalid page range." << std::endl;
        return 1;
    }

    QPDF output_pdf;
    output_pdf.emptyPDF();
    for (int i = from_page - 1; i < to_page; ++i) {
        QPDFObjectHandle src_page = all_pages.at(i);
        output_pdf.addPage(src_page, false);
    }

    std::string output_file = "output.pdf";
    QPDFWriter output_writer(output_pdf, output_file.c_str());
    output_writer.write();

    return 0;
}
