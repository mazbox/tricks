/*




 unsigned char *workingBuffer[1024];
 int workingLength = 0;
 void processLines(unsigned char *data, int length) {
 if(length+workingLength>1023) {
 printf("Buffer not big enough!\n");
 workingLength = 0;
 return;
 }
 
 
 
 
 
 // look at this buffer, decide what to read
 memcpy(workingBuffer+workingLength, data, length);
 
 workingLength += length;
 // put a null terminator on it
 workingBuffer[length] = 0;
 string s = (const char *)workingBuffer;
 
 int lastCarriageReturn = s.rfind("\r");
 
 if(lastCarriageReturn==-1) {
 printf("No CR's\n");
 // not enough data to process
 return;
 }
 
 s = s.substr(0, lastCarriageReturn);
 
 vector<string> parts = ofSplitString(s, "\r");
 
 // don't want to do this here, because it could
 // potentially leave serial routine blocking.
 for(int i = 0; i < parts.size(); i++) {
 printf("--> %s\n", parts[i].c_str());
 }
 
 
 const char *remainderStart = s.c_str()+lastCarriageReturn+1;
 int remainderLength = (s.length() - lastCarriageReturn);
 printf("Remainder Length: %d\n", remainderLength);
 //	memcpy(workingBuffer, remainderStart, remainderLength);
 workingLength = remainderLength;
 
 workingLength = 0;
 }


*/