#### Implementation Notes ####

I have implemented every testcase fully except for "testImgPlane.txt" where I couldn't get the
lighting quite right for the sphere that clips with the image plane.

#### BUILD / INSTALL Instructions ####
Assumption: On Graphics lab windows machine

Command Sequence starting at the root directory of the project folder:
1. mkdir bin
2. cd bin
3. cmake ../
4. cmake --build . --config Release
5. cmake --install .

RayTracer.exe will then be added to the root directory
