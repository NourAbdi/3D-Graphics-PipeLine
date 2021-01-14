***Nour Abdi 206144750***

**1.Load a mesh and make sure that it's visible on screen. Pick an axis (i.e. x; y or z), and
rotate the model around the axis. Scale the model such that it is always visible, no matter
the rotation. Apply the rotation around that axis in increments of 45degrees. Put screenshots
of the results in your report, and mention which axis you chose.** 

I chose the bethovenmodel and applied rotation around the y axis in increments of 45 degrees :

![45alpha](https://user-images.githubusercontent.com/34486030/101330747-ab3d8280-387b-11eb-8e67-d21137549b3b.png)

**2.Load a different mesh and pick two transformations T1; T2. Compare the results of ap-
plying T1 in model frame and T2 in world frame vs. T2 in world frame and T1 in world
frame.**

![Untitled](https://user-images.githubusercontent.com/34486030/101333556-6a476d00-387f-11eb-93f6-e2d0c0f9ddfc.png)
![t2 vs t1](https://user-images.githubusercontent.com/34486030/101333559-6ae00380-387f-11eb-8a2b-192d434361dd.png)
![55](https://user-images.githubusercontent.com/34486030/101333562-6b789a00-387f-11eb-9cee-e29344991101.png)
![Untitled111](https://user-images.githubusercontent.com/34486030/101333564-6b789a00-387f-11eb-93ff-23b297afa587.png)

**3.Reset the model's transformations. Display the bounding box, face normals and vertex
normals. Make sure the the normals are scaled reasonably (not too long that they cover
the whole screen, and not to short, that they look like points). Translate the model in
the x direction, and compare the results**

Here is bethoven model is transformed and obviously converting the normals in line with the model ...
Transforming the faces normals :
![lkjdabflkjabfdlkjdasb](https://user-images.githubusercontent.com/34486030/104592718-4e519b00-5677-11eb-9336-67aca24085e7.png)
![fdgdsfgdfkds](https://user-images.githubusercontent.com/34486030/104592725-4f82c800-5677-11eb-834c-19de1beb8377.png)
![sg,fkjsdfblaksdjfhasd](https://user-images.githubusercontent.com/34486030/104592728-4f82c800-5677-11eb-9b7c-36025925635f.png)
and now the same transformations on vertices normals ...
![df;lkasdf;lkasdhfsa](https://user-images.githubusercontent.com/34486030/104592807-704b1d80-5677-11eb-9a73-befd8fb95294.png)
![fsgsfgdsfdsf](https://user-images.githubusercontent.com/34486030/104592811-717c4a80-5677-11eb-9b34-0c56e16e0aa0.png)
![sfgsdfgkldsfjgh](https://user-images.githubusercontent.com/34486030/104592813-717c4a80-5677-11eb-831c-3d224bbe939c.png)

**4.Reset the model's transformations again, and set the camera away from the model. Com-
pare the orthographic projection vs. the perspective projection.**

![bunny](https://user-images.githubusercontent.com/34486030/101338159-471fbc00-3885-11eb-9677-ea6625c08a9b.png)
![bunny2](https://user-images.githubusercontent.com/34486030/101338160-47b85280-3885-11eb-973b-c7c9f26dce78.png)

**5.Set the projection to perspective. Show the difference between changing the zoom (by
changing the size of the frustum) and moving closer or farther from the model.**

![123](https://user-images.githubusercontent.com/34486030/101341351-a54e9e00-3889-11eb-9d37-b962235afd9f.png)
![321](https://user-images.githubusercontent.com/34486030/101341355-a67fcb00-3889-11eb-9b9b-0c3caddf758b.png)

**6.Rotate the camera in the camera's frame around the y (up) axis, such that the model is
placed close to the edge of the screen. Compare the result vs. rotating the camera in the
world frame.**

![8](https://user-images.githubusercontent.com/34486030/101340097-f6f62900-3887-11eb-9335-59714085e6a6.png)
![88](https://user-images.githubusercontent.com/34486030/101340100-f8275600-3887-11eb-9e23-b983cfa2248d.png)

**7.Set the camera position to (100,100,100) and orient it towards the origin using LookAt. Pick a
such that the model is clearly visible.**

![100](https://user-images.githubusercontent.com/34486030/101340546-92879980-3888-11eb-9fbc-6751b0c6ac3e.png)

**9.Resize the window two two diffferent sizes and show that your application maintains aspect ratio.**
first window is the default 1280x720 , the second is bigger than the first . Showing the diffrences and
how the model is not changing with size :

![555](https://user-images.githubusercontent.com/34486030/104463652-b5f5e080-55ba-11eb-954b-4664a3e92bda.png)
![666](https://user-images.githubusercontent.com/34486030/104463661-b9896780-55ba-11eb-95f9-d4757dce3fe7.png)

** Changing the scale matrix so the modle scale correct with correct transformations **
Here is some pictures of how modles are now displayed after the changing of the scale matrix:

![Untitled](https://user-images.githubusercontent.com/34486030/104498739-c6bb4c00-55e4-11eb-9392-14404e55925e.png)
![erad](https://user-images.githubusercontent.com/34486030/104499033-274a8900-55e5-11eb-9e6a-091fc136331a.png)
![sdfdsf](https://user-images.githubusercontent.com/34486030/104499047-2d406a00-55e5-11eb-94f4-6a4b334a52da.png)

