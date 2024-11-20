#include "Data.hh"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

using namespace std;
// take two data points and compare their difference with the error
bool Data::compare(Data i, Data j,int bin, int n) const {

  double diff = i.m_data[bin] - j.m_data[bin];
    if (diff ==0) return true;
  double error =  sqrt((i.m_data[bin] - j.m_data[bin]/(abs(diff))* i.m_error[bin])**2 + (j.m_data[bin] - i.m_data[bin]/(abs(diff))* j.m_error[bin])**2);
  return abs(diff) < n*error;
}
Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
    // read in data from file: error 
    for (int i = 0; i < size; ++i) {
      double error;
      file >> error;
      m_error.push_back(error);
    }

  // done! close the file
  file.close();

  assertSizes();
};
// check if two data sets are within n errors of each other and return the number that are not
int Data::checkCompatibility(const Data& in, int n) {
    int count = 0;
    for (int i = 0; i < m_data.size(); ++i) {
        if (!compare(i, in, n)) {
        count++;
        }
    }
    return count;


}
void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size()); }
