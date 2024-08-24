#ifndef PACKAGE_H
#define PACKAGE_H

/*
package:
0+subnet(2)+device(5)
0+subnetT(2)+deviceT(5)
0+serviceC(2)+service(5)
0+serviceCT(2)+serviceT(5)

package limits (from 0 to ...):
subnet:3
device:31
serviceC:3
service:31
*/
#include "WString.h"

class Package
{
public:
  Package(const String &content)
  {
    this->content = content; // Store the content string
    this->encoded_key_count = 4;
    this->binary_expression = ""; // Initialize binary expression as an empty string
  }

  static Package build(
      uint8_t _from, uint8_t _fsubnet, uint8_t _fservice_category, uint8_t _fservice,
      uint8_t _target, uint8_t _tsubnet, uint8_t _tservice_category, uint8_t _tservice,
      const String &data)
  {

    String content = "";
    String g0 = "0" + convertToBitString(_fsubnet, 2) + convertToBitString(_from, 5);

    String g1 = "0" + convertToBitString(_tsubnet, 2) + convertToBitString(_target, 5);

    String g2 = "0" + convertToBitString(_fservice_category, 2) + convertToBitString(_fservice, 5);

    String g3 = "0" + convertToBitString(_tservice_category, 2) + convertToBitString(_tservice, 5);

    content += encode(g0) + encode(g1) + encode(g2) + encode(g3) + data;

    return Package(content);
  }

  String parse()
  {
    if (binary_expression.length() == 0)
    {
      String devices = content.substring(0, encoded_key_count);
      for (int i = 0; i < devices.length(); i++)
      {
        binary_expression += byteToBitString(devices[i]);
      }
    }
    return binary_expression;
  }

  int fromSubnet()
  {
    return bitStringToInt(parse().substring(0, 3));
  }

  int from()
  {
    int start = 3;
    return bitStringToInt(parse().substring(start, start + 5));
  }

  int toSubnet()
  {
    return bitStringToInt(parse().substring(8, 8 + 3));
  }

  int to()
  {
    int start = 8 + 3;
    return bitStringToInt(parse().substring(start, start + 5));
  }

  int fromServiceCategory()
  {
    int start = 16;
    return bitStringToInt(parse().substring(start, start + 3));
  }

  int fromService()
  {
    int start = 16 + 3;
    return bitStringToInt(parse().substring(start, start + 5));
  }

  int toServiceCategory()
  {
    int start = 24;
    return bitStringToInt(parse().substring(start, start + 3));
  }

  int toService()
  {
    int start = 24 + 3;
    return bitStringToInt(parse().substring(start, start + 5));
  }

  String getData()
  {
    return content.substring(encoded_key_count);
  }
  String getContent()
  {
    return content;
  }

  String getHead()
  {
    return content.substring(0, encoded_key_count);
  }

  String toString()
  {
    parse();
    String result = "from subnet: " + String(fromSubnet());
    result += "\nfrom: " + String(from());
    result += "\nto subnet: " + String(toSubnet());
    result += "\nto: " + String(to());
    result += "\nfrom service category: " + String(fromServiceCategory());
    result += "\nfrom service: " + String(fromService());
    result += "\nto service category: " + String(toServiceCategory());
    result += "\nto service: " + String(toService());
    return result;
  }

private:
  String content;
  String binary_expression;
  int encoded_key_count;

  static String convertToBitString(uint8_t value, int bit_count)
  {
    String bitString = "";
    for (int i = bit_count - 1; i >= 0; i--)
    {
      bitString += bitRead(value, i);
    }
    return bitString;
  }

  static String byteToBitString(char byte)
  {
    String bitString = "";
    for (int i = 7; i >= 0; i--)
    {
      bitString += bitRead(byte, i);
    }
    return bitString;
  }

  static int bitStringToInt(const String &bitString)
  {
    int value = 0;
    for (int i = 0; i < bitString.length(); i++)
    {
      value = (value << 1) + (bitString[i] - '0');
    }
    return value;
  }

  // Function to encode a binary string to a UTF-8 character
  static String encode(const String &bitString)
  {
    // Check if the bit string length is valid
    if (bitString.length() != 8)
    {
      Serial.println("Error: bitString must be 8 bits long.");
      return "";
    }

    // Convert binary string to byte
    byte byteValue = 0;
    for (int i = 0; i < 8; i++)
    {
      if (bitString[i] == '1')
      {
        byteValue |= (1 << (7 - i)); // Set the corresponding bit
      }
      else if (bitString[i] != '0')
      {
        Serial.println("Error: bitString must contain only '0' or '1'.");
        return "";
      }
    }

    // Convert byte to UTF-8 character
    char utf8Char = static_cast<char>(byteValue);

    // Return as a String
    return String(utf8Char);
  }
};

#endif // PACKAGE_H
