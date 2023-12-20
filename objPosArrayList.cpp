#include "objPosArrayList.h"

objPosArrayList::objPosArrayList() {
    sizeList = 0;  // Initialize the size of the list
    sizeArray = ARRAY_MAX_CAP;  // Initialize the size of the array
    aList = new objPos[sizeArray];  // Allocate memory for the array
}

objPosArrayList::~objPosArrayList() {
    delete[] aList;  // Release the memory when the object is destroyed
}

int objPosArrayList::getSize() {
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos) {
    if (sizeList < sizeArray) {
        // Shift the existing elements to make room for the new element at the head
        for (int i = sizeList; i > 0; --i) {
            aList[i] = aList[i - 1];
        }
        // Insert the new element at the head
        aList[0] = thisPos;
        ++sizeList;  // Increase the size of the list
    }
}

void objPosArrayList::insertTail(objPos thisPos) {
    if (sizeList < sizeArray) {
        // Insert the new element at the tail
        aList[sizeList] = thisPos;
        ++sizeList;  // Increase the size of the list
    }
}

void objPosArrayList::removeHead() {
    if (sizeList > 0) {
        // Shift the elements to remove the element at the head
        for (int i = 0; i < sizeList - 1; ++i) {
            aList[i] = aList[i + 1];
        }
        --sizeList;  // Decrease the size of the list
    }
}

void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        --sizeList;  // Decrease the size of the list to remove the element at the tail
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index) {
    if (index >= 0 && index < sizeList) {
        returnPos = aList[index];
    }
}
