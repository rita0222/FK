SHELL	= /bin/sh

RM		= rm -f
CP		= cp

all:
	@echo "	macOS:			make mac"
	@echo "	macOS Dynamic:		make mac-d"
	@echo "	macOS Debug:		make mac-g"
	@echo "	Linux:			make linux"
	@echo "	Clean:			make clean"

mac:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	$(MAKE) mac -f Makefile_sub

mac-d:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-d TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-d TARGET=depend ; \
		$(MAKE) mac-d ; \
		cd .. ; done

mac-g:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-g TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-g TARGET=depend ; \
		$(MAKE) mac-g ; \
		cd .. ; done

linux:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) linux TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) linux TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) linux TARGET=depend ; \
		$(MAKE) linux ; \
		cd .. ; done

clean:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(MAKE) clean -f Makefile.plane ; \
		$(RM) Makefile ; \
		cd .. ; done

####################
# DO NOT DELETE!!!

OpenCL/OpenCL.o: ../FK/OpenCL.h ../FK/Error.H ../FK/Base.h
audio/Audio_Base.o: ../FK/Audio.h ../FK/IDAdmin.H ../FK/Vector.h ../FK/Base.h
audio/Audio_Base.o: ../FK/Error.H ../FK/Model.h ../FK/Boundary.h
audio/Audio_Base.o: ../FK/MatAdmin.h ../FK/Matrix.h ../FK/Angle.h
audio/Audio_Base.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/Material.h
audio/Audio_Base.o: ../FK/Color.h ../FK/RenderState.h ../FK/IndexFace.h
audio/Audio_Base.o: ../FK/FVecArray.h ../FK/ParserBase.H ../FK/ParserData.h
audio/Audio_Base.o: ../FK/Shape.h ../FK/Attribute.h ../FK/AttributeData.H
audio/Audio_Base.o: ../FK/OpenGL.H ../FK/Texture.h ../FK/Image.h ../FK/Tree.h
audio/Audio_Base.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Time.h
audio/Audio_Base.o: ../MacPack/include/vorbis/vorbisfile.h
audio/Audio_Base.o: ../MacPack/include/vorbis/codec.h
audio/Audio_Base.o: ../MacPack/include/ogg/ogg.h
audio/Audio_Base.o: ../MacPack/include/ogg/os_types.h
audio/Audio_Base.o: ../MacPack/include/ogg/config_types.h
audio/Audio_Base.o: ../MacPack/include/AL/al.h ../MacPack/include/AL/alc.h
audio/Audio_Buffer.o: ../FK/Audio.h ../FK/IDAdmin.H ../FK/Vector.h
audio/Audio_Buffer.o: ../FK/Base.h ../FK/Error.H ../FK/Model.h
audio/Audio_Buffer.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/Matrix.h
audio/Audio_Buffer.o: ../FK/Angle.h ../FK/DrawMode.h ../FK/Palette.h
audio/Audio_Buffer.o: ../FK/Material.h ../FK/Color.h ../FK/RenderState.h
audio/Audio_Buffer.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
audio/Audio_Buffer.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
audio/Audio_Buffer.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Texture.h
audio/Audio_Buffer.o: ../FK/Image.h ../FK/Tree.h
audio/Audio_Buffer.o: ../MacPack/include/vorbis/vorbisfile.h
audio/Audio_Buffer.o: ../MacPack/include/vorbis/codec.h
audio/Audio_Buffer.o: ../MacPack/include/ogg/ogg.h
audio/Audio_Buffer.o: ../MacPack/include/ogg/os_types.h
audio/Audio_Buffer.o: ../MacPack/include/ogg/config_types.h
audio/Audio_Buffer.o: ../MacPack/include/AL/al.h ../MacPack/include/AL/alc.h
audio/Audio_Stream.o: ../FK/Audio.h ../FK/IDAdmin.H ../FK/Vector.h
audio/Audio_Stream.o: ../FK/Base.h ../FK/Error.H
audio/Audio_Stream.o: ../MacPack/include/vorbis/vorbisfile.h
audio/Audio_Stream.o: ../MacPack/include/vorbis/codec.h
audio/Audio_Stream.o: ../MacPack/include/ogg/ogg.h
audio/Audio_Stream.o: ../MacPack/include/ogg/os_types.h
audio/Audio_Stream.o: ../MacPack/include/ogg/config_types.h
audio/Audio_Stream.o: ../MacPack/include/AL/al.h ../MacPack/include/AL/alc.h
base/Base.o: ../FK/Base.h
base/Error.o: ../FK/Error.H ../FK/Base.h
base/IDAdmin.o: ../FK/Base.h ../FK/IDAdmin.H ../FK/Error.H
base/System.o: ../FK/System.h ../FK/Base.h ../FK/Error.H
base/Tree.o: ../FK/Tree.h ../FK/Error.H ../FK/Base.h
graph/CostTable.o: ../FK/CostTable.H ../FK/GraphNode.h ../FK/GraphEdge.h
graph/CostTable.o: ../FK/Color.h ../FK/Base.h ../FK/Point.h ../FK/FVecArray.h
graph/CostTable.o: ../FK/Vector.h ../FK/Array.H ../FK/IDAdmin.H ../FK/Shape.h
graph/CostTable.o: ../FK/Palette.h ../FK/Material.h ../FK/Attribute.h
graph/CostTable.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Line.h
graph/CostTable.o: ../FK/LineBase.H ../FK/Window.h
graph/CostTable.o: ../MacPack/include/FL/Fl_Gl_Window.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Window.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Group.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Widget.H
graph/CostTable.o: ../MacPack/include/FL/Enumerations.H
graph/CostTable.o: ../MacPack/include/FL/abi-version.h
graph/CostTable.o: ../MacPack/include/FL/Fl_Export.H
graph/CostTable.o: ../MacPack/include/FL/fl_types.h
graph/CostTable.o: ../MacPack/include/FL/Fl_Bitmap.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Image.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Browser.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Browser_.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Scrollbar.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Slider.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Valuator.H
graph/CostTable.o: ../MacPack/include/FL/Fl.H
graph/CostTable.o: ../MacPack/include/FL/Fl_Export.H
graph/CostTable.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graph/CostTable.o: ../FK/Matrix.h ../FK/Angle.h ../FK/Image.h ../FK/DList.h
graph/CostTable.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
graph/CostTable.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
graph/CostTable.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/IndexFace.h
graph/CostTable.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Texture.h
graph/CostTable.o: ../FK/Tree.h ../FK/Light.h ../FK/FrameController.h
graph/Graph.o: ../FK/Graph.h ../FK/CostTable.H ../FK/GraphNode.h
graph/Graph.o: ../FK/GraphEdge.h ../FK/Color.h ../FK/Base.h ../FK/Point.h
graph/Graph.o: ../FK/FVecArray.h ../FK/Vector.h ../FK/Array.H ../FK/IDAdmin.H
graph/Graph.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
graph/Graph.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/OpenGL.H
graph/Graph.o: ../FK/Line.h ../FK/LineBase.H ../FK/Window.h
graph/Graph.o: ../MacPack/include/FL/Fl_Gl_Window.H
graph/Graph.o: ../MacPack/include/FL/Fl_Window.H
graph/Graph.o: ../MacPack/include/FL/Fl_Group.H
graph/Graph.o: ../MacPack/include/FL/Fl_Widget.H
graph/Graph.o: ../MacPack/include/FL/Enumerations.H
graph/Graph.o: ../MacPack/include/FL/abi-version.h
graph/Graph.o: ../MacPack/include/FL/Fl_Export.H
graph/Graph.o: ../MacPack/include/FL/fl_types.h
graph/Graph.o: ../MacPack/include/FL/Fl_Bitmap.H
graph/Graph.o: ../MacPack/include/FL/Fl_Image.H
graph/Graph.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graph/Graph.o: ../MacPack/include/FL/Fl_Browser.H
graph/Graph.o: ../MacPack/include/FL/Fl_Browser_.H
graph/Graph.o: ../MacPack/include/FL/Fl_Scrollbar.H
graph/Graph.o: ../MacPack/include/FL/Fl_Slider.H
graph/Graph.o: ../MacPack/include/FL/Fl_Valuator.H ../MacPack/include/FL/Fl.H
graph/Graph.o: ../MacPack/include/FL/Fl_Export.H
graph/Graph.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H ../FK/Matrix.h
graph/Graph.o: ../FK/Angle.h ../FK/Image.h ../FK/DList.h ../FK/Projection.h
graph/Graph.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h ../FK/Boundary.h
graph/Graph.o: ../FK/MatAdmin.h ../FK/DrawMode.h ../FK/RenderState.h
graph/Graph.o: ../FK/IndexFace.h ../FK/ParserBase.H ../FK/ParserData.h
graph/Graph.o: ../FK/Texture.h ../FK/Tree.h ../FK/Light.h
graph/Graph.o: ../FK/FrameController.h
graph/GraphEdge.o: ../FK/Graph.h ../FK/CostTable.H ../FK/GraphNode.h
graph/GraphEdge.o: ../FK/GraphEdge.h ../FK/Color.h ../FK/Base.h ../FK/Point.h
graph/GraphEdge.o: ../FK/FVecArray.h ../FK/Vector.h ../FK/Array.H
graph/GraphEdge.o: ../FK/IDAdmin.H ../FK/Shape.h ../FK/Palette.h
graph/GraphEdge.o: ../FK/Material.h ../FK/Attribute.h ../FK/AttributeData.H
graph/GraphEdge.o: ../FK/OpenGL.H ../FK/Line.h ../FK/LineBase.H
graph/GraphNode.o: ../FK/Graph.h ../FK/CostTable.H ../FK/GraphNode.h
graph/GraphNode.o: ../FK/GraphEdge.h ../FK/Color.h ../FK/Base.h ../FK/Point.h
graph/GraphNode.o: ../FK/FVecArray.h ../FK/Vector.h ../FK/Array.H
graph/GraphNode.o: ../FK/IDAdmin.H ../FK/Shape.h ../FK/Palette.h
graph/GraphNode.o: ../FK/Material.h ../FK/Attribute.h ../FK/AttributeData.H
graph/GraphNode.o: ../FK/OpenGL.H ../FK/Line.h ../FK/LineBase.H
graphics/BezCurveDraw.o: ../FK/BezCurveDraw.H ../FK/DrawBase.H ../FK/OpenGL.H
graphics/BezCurveDraw.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Base.h
graphics/BezCurveDraw.o: ../FK/Angle.h ../FK/Material.h ../FK/Color.h
graphics/BezCurveDraw.o: ../FK/Light.h ../FK/Shape.h ../FK/Palette.h
graphics/BezCurveDraw.o: ../FK/Attribute.h ../FK/AttributeData.H
graphics/BezCurveDraw.o: ../FK/ShaderBinder.h ../FK/AppWindow.h
graphics/BezCurveDraw.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Window.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Group.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Widget.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Enumerations.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/abi-version.h
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/fl_types.h
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Image.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Browser.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Slider.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/BezCurveDraw.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/BezCurveDraw.o: ../FK/Image.h ../FK/DList.h ../FK/Projection.h
graphics/BezCurveDraw.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
graphics/BezCurveDraw.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
graphics/BezCurveDraw.o: ../FK/RenderState.h ../FK/IndexFace.h
graphics/BezCurveDraw.o: ../FK/FVecArray.h ../FK/ParserBase.H
graphics/BezCurveDraw.o: ../FK/ParserData.h ../FK/Texture.h ../FK/Tree.h
graphics/BezCurveDraw.o: ../FK/FrameController.h ../FK/GuideObject.h
graphics/BezCurveDraw.o: ../FK/Line.h ../FK/LineBase.H ../FK/TrackBall.h
graphics/BezCurveDraw.o: ../FK/MotionCharactor.h ../FK/IFSTexture.h
graphics/BezCurveDraw.o: ../FK/Scene.h ../FK/Fog.h ../FK/MotionData.H
graphics/BezCurveDraw.o: ../FK/SpriteModel.h ../FK/UniCode.h
graphics/BezCurveDraw.o: ../FK/TextImage.h ../FK/RectTexture.h
graphics/BezCurveDraw.o: ../FK/Fullscreen.h ../FK/ShaderProgram.h
graphics/BezCurveDraw.o: ../FK/ShaderParameter.h ../FK/BezCurve.h
graphics/BezCurveDraw.o: ../FK/Curve.h ../FK/Point.h ../FK/Array.H
graphics/BezCurveDraw.o: ../FK/IDAdmin.H ../FK/RBezCurve.h ../FK/Error.H
graphics/BezCurveDraw.o: graphics/GLSL/Curve_VS.out
graphics/BezCurveDraw.o: graphics/GLSL/Curve_FS.out
graphics/BezCurveDraw.o: graphics/GLSL/Curve_Line_TE.out
graphics/BezCurveDraw.o: graphics/GLSL/Curve_Point_TE.out
graphics/DrawBase.o: ../FK/DrawBase.H ../FK/OpenGL.H ../FK/Matrix.h
graphics/DrawBase.o: ../FK/Vector.h ../FK/Base.h ../FK/Angle.h
graphics/DrawBase.o: ../FK/Material.h ../FK/Color.h ../FK/Light.h
graphics/DrawBase.o: ../FK/Shape.h ../FK/Palette.h ../FK/Attribute.h
graphics/DrawBase.o: ../FK/AttributeData.H ../FK/Model.h ../FK/Boundary.h
graphics/DrawBase.o: ../FK/MatAdmin.h ../FK/DrawMode.h ../FK/RenderState.h
graphics/DrawBase.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
graphics/DrawBase.o: ../FK/ParserData.h ../FK/Texture.h ../FK/Image.h
graphics/DrawBase.o: ../FK/Tree.h ../FK/ShaderBinder.h ../FK/AppWindow.h
graphics/DrawBase.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Window.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Group.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Widget.H
graphics/DrawBase.o: ../MacPack/include/FL/Enumerations.H
graphics/DrawBase.o: ../MacPack/include/FL/abi-version.h
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Export.H
graphics/DrawBase.o: ../MacPack/include/FL/fl_types.h
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Image.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Browser.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Slider.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl.H
graphics/DrawBase.o: ../MacPack/include/FL/Fl_Export.H
graphics/DrawBase.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/DrawBase.o: ../FK/DList.h ../FK/Projection.h ../FK/Math.h
graphics/DrawBase.o: ../FK/Quaternion.h ../FK/FrameController.h
graphics/DrawBase.o: ../FK/GuideObject.h ../FK/Line.h ../FK/LineBase.H
graphics/DrawBase.o: ../FK/TrackBall.h ../FK/MotionCharactor.h
graphics/DrawBase.o: ../FK/IFSTexture.h ../FK/Scene.h ../FK/Fog.h
graphics/DrawBase.o: ../FK/MotionData.H ../FK/SpriteModel.h ../FK/UniCode.h
graphics/DrawBase.o: ../FK/TextImage.h ../FK/RectTexture.h ../FK/Fullscreen.h
graphics/DrawBase.o: ../FK/ShaderProgram.h ../FK/ShaderParameter.h
graphics/Engine.o: ../FK/Error.H ../FK/Base.h ../FK/Engine.H ../FK/OpenGL.H
graphics/Engine.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h ../FK/Image.h
graphics/Engine.o: ../FK/Material.h ../FK/Color.h ../FK/DList.h
graphics/Engine.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
graphics/Engine.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
graphics/Engine.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/RenderState.h
graphics/Engine.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
graphics/Engine.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
graphics/Engine.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
graphics/Engine.o: ../FK/Light.h ../FK/Scene.h ../FK/Fog.h ../FK/Plane.h
graphics/Engine.o: ../FK/Curve.h ../FK/Line.h ../FK/LineBase.H ../FK/Point.h
graphics/Engine.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/Surface.h
graphics/Engine.o: ../FK/Graph.h ../FK/CostTable.H ../FK/GraphNode.h
graphics/Engine.o: ../FK/GraphEdge.h ../FK/PointDraw.H ../FK/DrawBase.H
graphics/Engine.o: ../FK/ShaderBinder.h ../FK/AppWindow.h ../FK/Window.h
graphics/Engine.o: ../MacPack/include/FL/Fl_Gl_Window.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Window.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Group.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Widget.H
graphics/Engine.o: ../MacPack/include/FL/Enumerations.H
graphics/Engine.o: ../MacPack/include/FL/abi-version.h
graphics/Engine.o: ../MacPack/include/FL/Fl_Export.H
graphics/Engine.o: ../MacPack/include/FL/fl_types.h
graphics/Engine.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Image.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Browser.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Slider.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/Engine.o: ../MacPack/include/FL/Fl.H
graphics/Engine.o: ../MacPack/include/FL/Fl_Export.H
graphics/Engine.o: ../MacPack/include/FL/fl_utf8.h ../FK/FrameController.h
graphics/Engine.o: ../FK/GuideObject.h ../FK/TrackBall.h
graphics/Engine.o: ../FK/MotionCharactor.h ../FK/IFSTexture.h
graphics/Engine.o: ../FK/MotionData.H ../FK/SpriteModel.h ../FK/UniCode.h
graphics/Engine.o: ../FK/TextImage.h ../FK/RectTexture.h ../FK/Fullscreen.h
graphics/Engine.o: ../FK/ShaderProgram.h ../FK/ShaderParameter.h
graphics/Engine.o: ../FK/LineDraw.H ../FK/FaceDraw.H ../FK/TextureDraw.H
graphics/Engine.o: ../FK/BezCurveDraw.H ../FK/SurfaceDraw.H
graphics/FaceDraw.o: ../FK/Error.H ../FK/Base.h ../FK/FaceDraw.H
graphics/FaceDraw.o: ../FK/DrawBase.H ../FK/OpenGL.H ../FK/Matrix.h
graphics/FaceDraw.o: ../FK/Vector.h ../FK/Angle.h ../FK/Material.h
graphics/FaceDraw.o: ../FK/Color.h ../FK/Light.h ../FK/Shape.h
graphics/FaceDraw.o: ../FK/Palette.h ../FK/Attribute.h ../FK/AttributeData.H
graphics/FaceDraw.o: ../FK/ShaderBinder.h ../FK/AppWindow.h ../FK/Window.h
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Gl_Window.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Window.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Group.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Widget.H
graphics/FaceDraw.o: ../MacPack/include/FL/Enumerations.H
graphics/FaceDraw.o: ../MacPack/include/FL/abi-version.h
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/FaceDraw.o: ../MacPack/include/FL/fl_types.h
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Image.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Browser.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Slider.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl.H
graphics/FaceDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/FaceDraw.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/FaceDraw.o: ../FK/Image.h ../FK/DList.h ../FK/Projection.h
graphics/FaceDraw.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
graphics/FaceDraw.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
graphics/FaceDraw.o: ../FK/RenderState.h ../FK/IndexFace.h ../FK/FVecArray.h
graphics/FaceDraw.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Texture.h
graphics/FaceDraw.o: ../FK/Tree.h ../FK/FrameController.h ../FK/GuideObject.h
graphics/FaceDraw.o: ../FK/Line.h ../FK/LineBase.H ../FK/TrackBall.h
graphics/FaceDraw.o: ../FK/MotionCharactor.h ../FK/IFSTexture.h ../FK/Scene.h
graphics/FaceDraw.o: ../FK/Fog.h ../FK/MotionData.H ../FK/SpriteModel.h
graphics/FaceDraw.o: ../FK/UniCode.h ../FK/TextImage.h ../FK/RectTexture.h
graphics/FaceDraw.o: ../FK/Fullscreen.h ../FK/ShaderProgram.h
graphics/FaceDraw.o: ../FK/ShaderParameter.h ../FK/Solid.h ../FK/SolidBase.h
graphics/FaceDraw.o: ../FK/Modify.h ../FK/Operation.h ../FK/DrawCache.h
graphics/FaceDraw.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
graphics/FaceDraw.o: ../FK/DataBase.H ../FK/IDAdmin.H ../FK/DataAccess.h
graphics/FaceDraw.o: ../FK/History.H ../FK/Command.H ../FK/Vertex.h
graphics/FaceDraw.o: ../FK/Half.h ../FK/Loop.h ../FK/Surface.h ../FK/Point.h
graphics/FaceDraw.o: ../FK/Array.H graphics/GLSL/Face_Phong_VS.out
graphics/FaceDraw.o: graphics/GLSL/Face_Phong_FS.out
graphics/FaceDraw.o: graphics/GLSL/Face_Gouraud_VS.out
graphics/FaceDraw.o: graphics/GLSL/Face_Gouraud_FS.out
graphics/FrameController.o: ../FK/FrameController.h ../FK/Base.h ../FK/Time.h
graphics/FrameController.o: ../FK/Error.H ../FK/Window.h
graphics/FrameController.o: ../MacPack/include/FL/Fl_Gl_Window.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Window.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Group.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Widget.H
graphics/FrameController.o: ../MacPack/include/FL/Enumerations.H
graphics/FrameController.o: ../MacPack/include/FL/abi-version.h
graphics/FrameController.o: ../MacPack/include/FL/Fl_Export.H
graphics/FrameController.o: ../MacPack/include/FL/fl_types.h
graphics/FrameController.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Image.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Browser.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Slider.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/FrameController.o: ../MacPack/include/FL/Fl.H
graphics/FrameController.o: ../MacPack/include/FL/Fl_Export.H
graphics/FrameController.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/FrameController.o: ../FK/OpenGL.H ../FK/Matrix.h ../FK/Vector.h
graphics/FrameController.o: ../FK/Angle.h ../FK/Image.h ../FK/Material.h
graphics/FrameController.o: ../FK/Color.h ../FK/DList.h ../FK/Projection.h
graphics/FrameController.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
graphics/FrameController.o: ../FK/Boundary.h ../FK/MatAdmin.h
graphics/FrameController.o: ../FK/DrawMode.h ../FK/Palette.h
graphics/FrameController.o: ../FK/RenderState.h ../FK/IndexFace.h
graphics/FrameController.o: ../FK/FVecArray.h ../FK/ParserBase.H
graphics/FrameController.o: ../FK/ParserData.h ../FK/Shape.h
graphics/FrameController.o: ../FK/Attribute.h ../FK/AttributeData.H
graphics/FrameController.o: ../FK/Texture.h ../FK/Tree.h ../FK/Light.h
graphics/LineDraw.o: ../FK/LineDraw.H ../FK/DrawBase.H ../FK/OpenGL.H
graphics/LineDraw.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Base.h ../FK/Angle.h
graphics/LineDraw.o: ../FK/Material.h ../FK/Color.h ../FK/Light.h
graphics/LineDraw.o: ../FK/Shape.h ../FK/Palette.h ../FK/Attribute.h
graphics/LineDraw.o: ../FK/AttributeData.H ../FK/ShaderBinder.h
graphics/LineDraw.o: ../FK/AppWindow.h ../FK/Window.h
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Gl_Window.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Window.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Group.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Widget.H
graphics/LineDraw.o: ../MacPack/include/FL/Enumerations.H
graphics/LineDraw.o: ../MacPack/include/FL/abi-version.h
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/LineDraw.o: ../MacPack/include/FL/fl_types.h
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Image.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Browser.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Slider.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl.H
graphics/LineDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/LineDraw.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/LineDraw.o: ../FK/Image.h ../FK/DList.h ../FK/Projection.h
graphics/LineDraw.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
graphics/LineDraw.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
graphics/LineDraw.o: ../FK/RenderState.h ../FK/IndexFace.h ../FK/FVecArray.h
graphics/LineDraw.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Texture.h
graphics/LineDraw.o: ../FK/Tree.h ../FK/FrameController.h ../FK/GuideObject.h
graphics/LineDraw.o: ../FK/Line.h ../FK/LineBase.H ../FK/TrackBall.h
graphics/LineDraw.o: ../FK/MotionCharactor.h ../FK/IFSTexture.h ../FK/Scene.h
graphics/LineDraw.o: ../FK/Fog.h ../FK/MotionData.H ../FK/SpriteModel.h
graphics/LineDraw.o: ../FK/UniCode.h ../FK/TextImage.h ../FK/RectTexture.h
graphics/LineDraw.o: ../FK/Fullscreen.h ../FK/ShaderProgram.h
graphics/LineDraw.o: ../FK/ShaderParameter.h ../FK/Curve.h ../FK/Point.h
graphics/LineDraw.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/Surface.h
graphics/LineDraw.o: ../FK/Solid.h ../FK/SolidBase.h ../FK/Modify.h
graphics/LineDraw.o: ../FK/Operation.h ../FK/DrawCache.h ../FK/Reference.h
graphics/LineDraw.o: ../FK/Edge.h ../FK/Topology.h ../FK/DataBase.H
graphics/LineDraw.o: ../FK/DataAccess.h ../FK/History.H ../FK/Command.H
graphics/LineDraw.o: ../FK/Vertex.h ../FK/Half.h ../FK/Error.H
graphics/LineDraw.o: graphics/GLSL/Line_VS.out graphics/GLSL/Line_FS.out
graphics/PointDraw.o: ../FK/PointDraw.H ../FK/DrawBase.H ../FK/OpenGL.H
graphics/PointDraw.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Base.h
graphics/PointDraw.o: ../FK/Angle.h ../FK/Material.h ../FK/Color.h
graphics/PointDraw.o: ../FK/Light.h ../FK/Shape.h ../FK/Palette.h
graphics/PointDraw.o: ../FK/Attribute.h ../FK/AttributeData.H
graphics/PointDraw.o: ../FK/ShaderBinder.h ../FK/AppWindow.h ../FK/Window.h
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Gl_Window.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Window.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Group.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Widget.H
graphics/PointDraw.o: ../MacPack/include/FL/Enumerations.H
graphics/PointDraw.o: ../MacPack/include/FL/abi-version.h
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/PointDraw.o: ../MacPack/include/FL/fl_types.h
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Image.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Browser.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Slider.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl.H
graphics/PointDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/PointDraw.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/PointDraw.o: ../FK/Image.h ../FK/DList.h ../FK/Projection.h
graphics/PointDraw.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
graphics/PointDraw.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
graphics/PointDraw.o: ../FK/RenderState.h ../FK/IndexFace.h ../FK/FVecArray.h
graphics/PointDraw.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Texture.h
graphics/PointDraw.o: ../FK/Tree.h ../FK/FrameController.h
graphics/PointDraw.o: ../FK/GuideObject.h ../FK/Line.h ../FK/LineBase.H
graphics/PointDraw.o: ../FK/TrackBall.h ../FK/MotionCharactor.h
graphics/PointDraw.o: ../FK/IFSTexture.h ../FK/Scene.h ../FK/Fog.h
graphics/PointDraw.o: ../FK/MotionData.H ../FK/SpriteModel.h ../FK/UniCode.h
graphics/PointDraw.o: ../FK/TextImage.h ../FK/RectTexture.h
graphics/PointDraw.o: ../FK/Fullscreen.h ../FK/ShaderProgram.h
graphics/PointDraw.o: ../FK/ShaderParameter.h ../FK/Point.h ../FK/Array.H
graphics/PointDraw.o: ../FK/IDAdmin.H ../FK/Solid.h ../FK/SolidBase.h
graphics/PointDraw.o: ../FK/Modify.h ../FK/Operation.h ../FK/DrawCache.h
graphics/PointDraw.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
graphics/PointDraw.o: ../FK/DataBase.H ../FK/DataAccess.h ../FK/History.H
graphics/PointDraw.o: ../FK/Command.H ../FK/Vertex.h ../FK/Curve.h
graphics/PointDraw.o: ../FK/Surface.h ../FK/Graph.h ../FK/CostTable.H
graphics/PointDraw.o: ../FK/GraphNode.h ../FK/GraphEdge.h ../FK/Error.H
graphics/PointDraw.o: graphics/GLSL/Point_VS.out graphics/GLSL/Point_FS.out
graphics/SurfaceDraw.o: ../FK/SurfaceDraw.H ../FK/DrawBase.H ../FK/OpenGL.H
graphics/SurfaceDraw.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Base.h
graphics/SurfaceDraw.o: ../FK/Angle.h ../FK/Material.h ../FK/Color.h
graphics/SurfaceDraw.o: ../FK/Light.h ../FK/Shape.h ../FK/Palette.h
graphics/SurfaceDraw.o: ../FK/Attribute.h ../FK/AttributeData.H
graphics/SurfaceDraw.o: ../FK/ShaderBinder.h ../FK/AppWindow.h ../FK/Window.h
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Gl_Window.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Window.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Group.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Widget.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Enumerations.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/abi-version.h
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/fl_types.h
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Image.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Browser.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Slider.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/SurfaceDraw.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/SurfaceDraw.o: ../FK/Image.h ../FK/DList.h ../FK/Projection.h
graphics/SurfaceDraw.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
graphics/SurfaceDraw.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
graphics/SurfaceDraw.o: ../FK/RenderState.h ../FK/IndexFace.h
graphics/SurfaceDraw.o: ../FK/FVecArray.h ../FK/ParserBase.H
graphics/SurfaceDraw.o: ../FK/ParserData.h ../FK/Texture.h ../FK/Tree.h
graphics/SurfaceDraw.o: ../FK/FrameController.h ../FK/GuideObject.h
graphics/SurfaceDraw.o: ../FK/Line.h ../FK/LineBase.H ../FK/TrackBall.h
graphics/SurfaceDraw.o: ../FK/MotionCharactor.h ../FK/IFSTexture.h
graphics/SurfaceDraw.o: ../FK/Scene.h ../FK/Fog.h ../FK/MotionData.H
graphics/SurfaceDraw.o: ../FK/SpriteModel.h ../FK/UniCode.h ../FK/TextImage.h
graphics/SurfaceDraw.o: ../FK/RectTexture.h ../FK/Fullscreen.h
graphics/SurfaceDraw.o: ../FK/ShaderProgram.h ../FK/ShaderParameter.h
graphics/SurfaceDraw.o: ../FK/BezSurface.h ../FK/Surface.h ../FK/Point.h
graphics/SurfaceDraw.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/Error.H
graphics/SurfaceDraw.o: graphics/GLSL/Surface_VS.out
graphics/SurfaceDraw.o: graphics/GLSL/Surface_FS.out
graphics/SurfaceDraw.o: graphics/GLSL/Surface_Face_TE.out
graphics/SurfaceDraw.o: graphics/GLSL/Surface_Line_FS.out
graphics/SurfaceDraw.o: graphics/GLSL/Surface_Line_TE.out
graphics/SurfaceDraw.o: graphics/GLSL/Surface_Line_GS.out
graphics/SurfaceDraw.o: graphics/GLSL/Surface_Point_TE.out
graphics/TextureDraw.o: ../FK/TextureDraw.H ../FK/DrawBase.H ../FK/OpenGL.H
graphics/TextureDraw.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Base.h
graphics/TextureDraw.o: ../FK/Angle.h ../FK/Material.h ../FK/Color.h
graphics/TextureDraw.o: ../FK/Light.h ../FK/Shape.h ../FK/Palette.h
graphics/TextureDraw.o: ../FK/Attribute.h ../FK/AttributeData.H
graphics/TextureDraw.o: ../FK/ShaderBinder.h ../FK/AppWindow.h ../FK/Window.h
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Gl_Window.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Window.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Group.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Widget.H
graphics/TextureDraw.o: ../MacPack/include/FL/Enumerations.H
graphics/TextureDraw.o: ../MacPack/include/FL/abi-version.h
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/TextureDraw.o: ../MacPack/include/FL/fl_types.h
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Bitmap.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Image.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Multi_Browser.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Browser.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Browser_.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Scrollbar.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Slider.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Valuator.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl.H
graphics/TextureDraw.o: ../MacPack/include/FL/Fl_Export.H
graphics/TextureDraw.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
graphics/TextureDraw.o: ../FK/Image.h ../FK/DList.h ../FK/Projection.h
graphics/TextureDraw.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
graphics/TextureDraw.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
graphics/TextureDraw.o: ../FK/RenderState.h ../FK/IndexFace.h
graphics/TextureDraw.o: ../FK/FVecArray.h ../FK/ParserBase.H
graphics/TextureDraw.o: ../FK/ParserData.h ../FK/Texture.h ../FK/Tree.h
graphics/TextureDraw.o: ../FK/FrameController.h ../FK/GuideObject.h
graphics/TextureDraw.o: ../FK/Line.h ../FK/LineBase.H ../FK/TrackBall.h
graphics/TextureDraw.o: ../FK/MotionCharactor.h ../FK/IFSTexture.h
graphics/TextureDraw.o: ../FK/Scene.h ../FK/Fog.h ../FK/MotionData.H
graphics/TextureDraw.o: ../FK/SpriteModel.h ../FK/UniCode.h ../FK/TextImage.h
graphics/TextureDraw.o: ../FK/RectTexture.h ../FK/Fullscreen.h
graphics/TextureDraw.o: ../FK/ShaderProgram.h ../FK/ShaderParameter.h
graphics/TextureDraw.o: ../FK/Error.H graphics/GLSL/Texture_Phong_VS.out
graphics/TextureDraw.o: graphics/GLSL/Texture_Phong_FS.out
graphics/TextureDraw.o: graphics/GLSL/Texture_Gouraud_VS.out
graphics/TextureDraw.o: graphics/GLSL/Texture_Gouraud_FS.out
material/Color.o: ../FK/Color.h ../FK/Base.h ../FK/Math.h ../FK/Quaternion.h
material/Color.o: ../FK/Vector.h ../FK/Angle.h ../FK/Matrix.h
material/MatExample.o: ../FK/Material.h ../FK/Color.h ../FK/Base.h
material/MatExample.o: ../FK/MatExample.h
material/Material.o: ../FK/Material.h ../FK/Color.h ../FK/Base.h
material/Material.o: ../FK/MatExample.h ../FK/Error.H
material/Palette.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
material/Palette.o: ../FK/Base.h ../FK/Error.H
math/Angle.o: ../FK/Angle.h ../FK/Base.h ../FK/Error.H
math/FVecArray.o: ../FK/FVecArray.h ../FK/Vector.h ../FK/Base.h
math/FVecArray.o: ../FK/Material.h ../FK/Color.h
math/GenMatrix.o: ../FK/GenMatrix.h ../FK/GenVector.h ../FK/Vector.h
math/GenMatrix.o: ../FK/Base.h ../FK/Matrix.h ../FK/Angle.h ../FK/Error.H
math/GenVector.o: ../FK/GenVector.h ../FK/Vector.h ../FK/Base.h ../FK/Error.H
math/Math.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Vector.h ../FK/Base.h
math/Math.o: ../FK/Angle.h ../FK/Matrix.h
math/Matrix.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Base.h ../FK/Angle.h
math/Matrix.o: ../FK/Error.H
math/Plane.o: ../FK/Plane.h ../FK/Vector.h ../FK/Base.h ../FK/Matrix.h
math/Plane.o: ../FK/Angle.h ../FK/Math.h ../FK/Quaternion.h
math/Quaternion.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Vector.h
math/Quaternion.o: ../FK/Base.h ../FK/Angle.h ../FK/Matrix.h ../FK/Error.H
math/Vector.o: ../FK/Vector.h ../FK/Base.h ../FK/Error.H
model/BVHMotion.o: ../FK/BVHMotion.h ../FK/ParserBase.H ../FK/ParserData.h
model/BVHMotion.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
model/BVHMotion.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
model/BVHMotion.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Model.h
model/BVHMotion.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/Matrix.h
model/BVHMotion.o: ../FK/Angle.h ../FK/DrawMode.h ../FK/RenderState.h
model/BVHMotion.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/Texture.h
model/BVHMotion.o: ../FK/Image.h ../FK/Tree.h ../FK/Math.h ../FK/Quaternion.h
model/BVHMotion.o: ../FK/Error.H
model/Boundary.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
model/Boundary.o: ../FK/Base.h ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h
model/Boundary.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/Material.h
model/Boundary.o: ../FK/Color.h ../FK/RenderState.h ../FK/IndexFace.h
model/Boundary.o: ../FK/FVecArray.h ../FK/ParserBase.H ../FK/ParserData.h
model/Boundary.o: ../FK/Shape.h ../FK/Attribute.h ../FK/AttributeData.H
model/Boundary.o: ../FK/OpenGL.H ../FK/Texture.h ../FK/Image.h ../FK/Tree.h
model/BoundaryElem.o: ../FK/BoundaryElem.H ../FK/Base.h ../FK/Matrix.h
model/BoundaryElem.o: ../FK/Vector.h ../FK/Angle.h ../FK/Math.h
model/BoundaryElem.o: ../FK/Quaternion.h ../FK/IndexFace.h ../FK/FVecArray.h
model/BoundaryElem.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Shape.h
model/BoundaryElem.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
model/BoundaryElem.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/OpenGL.H
model/BoundaryElem.o: ../FK/Solid.h ../FK/SolidBase.h ../FK/Modify.h
model/BoundaryElem.o: ../FK/Operation.h ../FK/DrawCache.h ../FK/Reference.h
model/BoundaryElem.o: ../FK/Edge.h ../FK/Topology.h ../FK/DataBase.H
model/BoundaryElem.o: ../FK/IDAdmin.H ../FK/DataAccess.h ../FK/History.H
model/BoundaryElem.o: ../FK/Command.H ../FK/Vertex.h ../FK/Point.h
model/BoundaryElem.o: ../FK/Array.H ../FK/RectTexture.h ../FK/Texture.h
model/BoundaryElem.o: ../FK/Image.h ../FK/TriTexture.h ../FK/MeshTexture.h
model/BoundaryElem.o: ../FK/IFSTexture.h ../FK/Error.H
model/DrawMode.o: ../FK/DrawMode.h
model/MatAdmin.o: ../FK/MatAdmin.h ../FK/Base.h ../FK/Matrix.h ../FK/Vector.h
model/MatAdmin.o: ../FK/Angle.h ../FK/Quaternion.h ../FK/Math.h ../FK/Error.H
model/Model.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h ../FK/Base.h
model/Model.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h ../FK/DrawMode.h
model/Model.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
model/Model.o: ../FK/RenderState.h ../FK/IndexFace.h ../FK/FVecArray.h
model/Model.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Shape.h
model/Model.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/OpenGL.H
model/Model.o: ../FK/Texture.h ../FK/Image.h ../FK/Tree.h ../FK/Quaternion.h
model/Model.o: ../FK/BoundaryElem.H ../FK/Math.h
model/ModelTree.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
model/ModelTree.o: ../FK/Base.h ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h
model/ModelTree.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/Material.h
model/ModelTree.o: ../FK/Color.h ../FK/RenderState.h ../FK/IndexFace.h
model/ModelTree.o: ../FK/FVecArray.h ../FK/ParserBase.H ../FK/ParserData.h
model/ModelTree.o: ../FK/Shape.h ../FK/Attribute.h ../FK/AttributeData.H
model/ModelTree.o: ../FK/OpenGL.H ../FK/Texture.h ../FK/Image.h ../FK/Tree.h
model/ModelTree.o: ../FK/Error.H
scene/DList.o: ../FK/DList.h ../FK/Projection.h ../FK/Matrix.h ../FK/Vector.h
scene/DList.o: ../FK/Base.h ../FK/Angle.h ../FK/Math.h ../FK/Quaternion.h
scene/DList.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
scene/DList.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/Material.h
scene/DList.o: ../FK/Color.h ../FK/RenderState.h ../FK/IndexFace.h
scene/DList.o: ../FK/FVecArray.h ../FK/ParserBase.H ../FK/ParserData.h
scene/DList.o: ../FK/Shape.h ../FK/Attribute.h ../FK/AttributeData.H
scene/DList.o: ../FK/OpenGL.H ../FK/Texture.h ../FK/Image.h ../FK/Tree.h
scene/DList.o: ../FK/Light.h ../FK/IDAdmin.H ../FK/Window.h
scene/DList.o: ../MacPack/include/FL/Fl_Gl_Window.H
scene/DList.o: ../MacPack/include/FL/Fl_Window.H
scene/DList.o: ../MacPack/include/FL/Fl_Group.H
scene/DList.o: ../MacPack/include/FL/Fl_Widget.H
scene/DList.o: ../MacPack/include/FL/Enumerations.H
scene/DList.o: ../MacPack/include/FL/abi-version.h
scene/DList.o: ../MacPack/include/FL/Fl_Export.H
scene/DList.o: ../MacPack/include/FL/fl_types.h
scene/DList.o: ../MacPack/include/FL/Fl_Bitmap.H
scene/DList.o: ../MacPack/include/FL/Fl_Image.H
scene/DList.o: ../MacPack/include/FL/Fl_Multi_Browser.H
scene/DList.o: ../MacPack/include/FL/Fl_Browser.H
scene/DList.o: ../MacPack/include/FL/Fl_Browser_.H
scene/DList.o: ../MacPack/include/FL/Fl_Scrollbar.H
scene/DList.o: ../MacPack/include/FL/Fl_Slider.H
scene/DList.o: ../MacPack/include/FL/Fl_Valuator.H ../MacPack/include/FL/Fl.H
scene/DList.o: ../MacPack/include/FL/Fl_Export.H
scene/DList.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
scene/DList.o: ../FK/FrameController.h
scene/Fog.o: ../FK/Fog.h ../FK/Material.h ../FK/Color.h ../FK/Base.h
scene/Fog.o: ../FK/DList.h ../FK/Projection.h ../FK/Matrix.h ../FK/Vector.h
scene/Fog.o: ../FK/Angle.h ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
scene/Fog.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
scene/Fog.o: ../FK/Palette.h ../FK/RenderState.h ../FK/IndexFace.h
scene/Fog.o: ../FK/FVecArray.h ../FK/ParserBase.H ../FK/ParserData.h
scene/Fog.o: ../FK/Shape.h ../FK/Attribute.h ../FK/AttributeData.H
scene/Fog.o: ../FK/OpenGL.H ../FK/Texture.h ../FK/Image.h ../FK/Tree.h
scene/Fog.o: ../FK/Light.h
scene/Projection.o: ../FK/Projection.h ../FK/Matrix.h ../FK/Vector.h
scene/Projection.o: ../FK/Base.h ../FK/Angle.h ../FK/Math.h
scene/Projection.o: ../FK/Quaternion.h ../FK/Error.H
scene/Scene.o: ../FK/Scene.h ../FK/Fog.h ../FK/Material.h ../FK/Color.h
scene/Scene.o: ../FK/Base.h ../FK/DList.h ../FK/Projection.h ../FK/Matrix.h
scene/Scene.o: ../FK/Vector.h ../FK/Angle.h ../FK/Math.h ../FK/Quaternion.h
scene/Scene.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
scene/Scene.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/RenderState.h
scene/Scene.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
scene/Scene.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
scene/Scene.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Texture.h
scene/Scene.o: ../FK/Image.h ../FK/Tree.h ../FK/Light.h
shader/ShaderBinder.o: ../FK/ShaderBinder.h ../FK/AppWindow.h ../FK/Window.h
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Gl_Window.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Window.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Group.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Widget.H
shader/ShaderBinder.o: ../MacPack/include/FL/Enumerations.H
shader/ShaderBinder.o: ../MacPack/include/FL/abi-version.h
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Export.H
shader/ShaderBinder.o: ../MacPack/include/FL/fl_types.h
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Bitmap.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Image.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Multi_Browser.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Browser.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Browser_.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Scrollbar.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Slider.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Valuator.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl.H
shader/ShaderBinder.o: ../MacPack/include/FL/Fl_Export.H
shader/ShaderBinder.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
shader/ShaderBinder.o: ../FK/Base.h ../FK/OpenGL.H ../FK/Matrix.h
shader/ShaderBinder.o: ../FK/Vector.h ../FK/Angle.h ../FK/Image.h
shader/ShaderBinder.o: ../FK/Material.h ../FK/Color.h ../FK/DList.h
shader/ShaderBinder.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
shader/ShaderBinder.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
shader/ShaderBinder.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/RenderState.h
shader/ShaderBinder.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
shader/ShaderBinder.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
shader/ShaderBinder.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
shader/ShaderBinder.o: ../FK/Light.h ../FK/FrameController.h
shader/ShaderBinder.o: ../FK/GuideObject.h ../FK/Line.h ../FK/LineBase.H
shader/ShaderBinder.o: ../FK/TrackBall.h ../FK/MotionCharactor.h
shader/ShaderBinder.o: ../FK/IFSTexture.h ../FK/Scene.h ../FK/Fog.h
shader/ShaderBinder.o: ../FK/MotionData.H ../FK/SpriteModel.h ../FK/UniCode.h
shader/ShaderBinder.o: ../FK/TextImage.h ../FK/RectTexture.h
shader/ShaderBinder.o: ../FK/Fullscreen.h ../FK/ShaderProgram.h
shader/ShaderBinder.o: ../FK/ShaderParameter.h ../FK/DrawBase.H
shader/ShaderBinder.o: shader/GLSL/FBO_Vertex.out shader/GLSL/FBO_Geom.out
shader/ShaderParameter.o: ../FK/ShaderProgram.h ../FK/Engine.H ../FK/Base.h
shader/ShaderParameter.o: ../FK/OpenGL.H ../FK/Matrix.h ../FK/Vector.h
shader/ShaderParameter.o: ../FK/Angle.h ../FK/Image.h ../FK/Material.h
shader/ShaderParameter.o: ../FK/Color.h ../FK/DList.h ../FK/Projection.h
shader/ShaderParameter.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
shader/ShaderParameter.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
shader/ShaderParameter.o: ../FK/Palette.h ../FK/RenderState.h
shader/ShaderParameter.o: ../FK/IndexFace.h ../FK/FVecArray.h
shader/ShaderParameter.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Shape.h
shader/ShaderParameter.o: ../FK/Attribute.h ../FK/AttributeData.H
shader/ShaderParameter.o: ../FK/Texture.h ../FK/Tree.h ../FK/Light.h
shader/ShaderParameter.o: ../FK/ShaderParameter.h ../FK/Window.h
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Gl_Window.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Window.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Group.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Widget.H
shader/ShaderParameter.o: ../MacPack/include/FL/Enumerations.H
shader/ShaderParameter.o: ../MacPack/include/FL/abi-version.h
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Export.H
shader/ShaderParameter.o: ../MacPack/include/FL/fl_types.h
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Bitmap.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Image.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Multi_Browser.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Browser.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Browser_.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Scrollbar.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Slider.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Valuator.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl.H
shader/ShaderParameter.o: ../MacPack/include/FL/Fl_Export.H
shader/ShaderParameter.o: ../MacPack/include/FL/fl_utf8.h
shader/ShaderParameter.o: ../FK/FrameController.h
shader/ShaderProgram.o: ../FK/ShaderProgram.h ../FK/Engine.H ../FK/Base.h
shader/ShaderProgram.o: ../FK/OpenGL.H ../FK/Matrix.h ../FK/Vector.h
shader/ShaderProgram.o: ../FK/Angle.h ../FK/Image.h ../FK/Material.h
shader/ShaderProgram.o: ../FK/Color.h ../FK/DList.h ../FK/Projection.h
shader/ShaderProgram.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Model.h
shader/ShaderProgram.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
shader/ShaderProgram.o: ../FK/Palette.h ../FK/RenderState.h ../FK/IndexFace.h
shader/ShaderProgram.o: ../FK/FVecArray.h ../FK/ParserBase.H
shader/ShaderProgram.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
shader/ShaderProgram.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
shader/ShaderProgram.o: ../FK/Light.h ../FK/ShaderParameter.h ../FK/Window.h
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Gl_Window.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Window.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Group.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Widget.H
shader/ShaderProgram.o: ../MacPack/include/FL/Enumerations.H
shader/ShaderProgram.o: ../MacPack/include/FL/abi-version.h
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Export.H
shader/ShaderProgram.o: ../MacPack/include/FL/fl_types.h
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Bitmap.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Image.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Multi_Browser.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Browser.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Browser_.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Scrollbar.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Slider.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Valuator.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl.H
shader/ShaderProgram.o: ../MacPack/include/FL/Fl_Export.H
shader/ShaderProgram.o: ../MacPack/include/FL/fl_utf8.h
shader/ShaderProgram.o: ../FK/FrameController.h shader/GLSL/Uniform.out
shader/ShaderProgram.o: shader/GLSL/Attribute.out shader/GLSL/Struct.out
shader/ShaderProgram.o: shader/GLSL/Fragment.out shader/GLSL/FBO_BuildIn.out
shape/Attribute.o: ../FK/AttributeData.H ../FK/Attribute.h ../FK/Base.h
shape/AttributeData.o: ../FK/Base.h ../FK/AttributeData.H ../FK/Error.H
shape/BSplBase.o: ../FK/BSplBase.H ../FK/Math.h ../FK/Quaternion.h
shape/BSplBase.o: ../FK/Vector.h ../FK/Base.h ../FK/Angle.h ../FK/Matrix.h
shape/BSplCurve.o: ../FK/BSplCurve.h ../FK/Curve.h ../FK/Vector.h
shape/BSplCurve.o: ../FK/Base.h ../FK/FVecArray.h ../FK/Line.h
shape/BSplCurve.o: ../FK/LineBase.H ../FK/Shape.h ../FK/Palette.h
shape/BSplCurve.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/BSplCurve.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Point.h
shape/BSplCurve.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/BSplBase.H
shape/BezCurve.o: ../FK/BezCurve.h ../FK/Curve.h ../FK/Vector.h ../FK/Base.h
shape/BezCurve.o: ../FK/FVecArray.h ../FK/Line.h ../FK/LineBase.H
shape/BezCurve.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
shape/BezCurve.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
shape/BezCurve.o: ../FK/OpenGL.H ../FK/Point.h ../FK/Array.H ../FK/IDAdmin.H
shape/BezCurve.o: ../FK/Matrix.h ../FK/Angle.h ../FK/Math.h
shape/BezCurve.o: ../FK/Quaternion.h ../FK/Error.H
shape/BezSurface.o: ../FK/BezSurface.h ../FK/Surface.h ../FK/Vector.h
shape/BezSurface.o: ../FK/Base.h ../FK/FVecArray.h ../FK/Line.h
shape/BezSurface.o: ../FK/LineBase.H ../FK/Shape.h ../FK/Palette.h
shape/BezSurface.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/BezSurface.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Point.h
shape/BezSurface.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/Math.h
shape/BezSurface.o: ../FK/Quaternion.h ../FK/Angle.h ../FK/Matrix.h
shape/BezSurface.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Window.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Group.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Widget.H
shape/BezSurface.o: ../MacPack/include/FL/Enumerations.H
shape/BezSurface.o: ../MacPack/include/FL/abi-version.h
shape/BezSurface.o: ../MacPack/include/FL/Fl_Export.H
shape/BezSurface.o: ../MacPack/include/FL/fl_types.h
shape/BezSurface.o: ../MacPack/include/FL/Fl_Bitmap.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Image.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Multi_Browser.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Browser.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Browser_.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Scrollbar.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Slider.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Valuator.H
shape/BezSurface.o: ../MacPack/include/FL/Fl.H
shape/BezSurface.o: ../MacPack/include/FL/Fl_Export.H
shape/BezSurface.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
shape/BezSurface.o: ../FK/Image.h ../FK/DList.h ../FK/Projection.h
shape/BezSurface.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
shape/BezSurface.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/IndexFace.h
shape/BezSurface.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Texture.h
shape/BezSurface.o: ../FK/Tree.h ../FK/Light.h ../FK/FrameController.h
shape/Block.o: ../FK/Block.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/Block.o: ../FK/Vector.h ../FK/Base.h ../FK/ParserBase.H
shape/Block.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Palette.h
shape/Block.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Block.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Capsule.o: ../FK/Capsule.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/Capsule.o: ../FK/Vector.h ../FK/Base.h ../FK/ParserBase.H
shape/Capsule.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Palette.h
shape/Capsule.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Capsule.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Circle.o: ../FK/Circle.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/Circle.o: ../FK/Vector.h ../FK/Base.h ../FK/ParserBase.H
shape/Circle.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Palette.h
shape/Circle.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Circle.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Closedline.o: ../FK/Closedline.h ../FK/LineBase.H ../FK/FVecArray.h
shape/Closedline.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/Closedline.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Closedline.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Cone.o: ../FK/Cone.h ../FK/IndexFace.h ../FK/FVecArray.h ../FK/Vector.h
shape/Cone.o: ../FK/Base.h ../FK/ParserBase.H ../FK/ParserData.h
shape/Cone.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h ../FK/Color.h
shape/Cone.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/OpenGL.H
shape/Curve.o: ../FK/Curve.h ../FK/Vector.h ../FK/Base.h ../FK/FVecArray.h
shape/Curve.o: ../FK/Line.h ../FK/LineBase.H ../FK/Shape.h ../FK/Palette.h
shape/Curve.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Curve.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Point.h
shape/Curve.o: ../FK/Array.H ../FK/IDAdmin.H
shape/D3DXAnimation.o: ../FK/D3DXAnimation.H ../FK/ParserBase.H
shape/D3DXAnimation.o: ../FK/ParserData.h ../FK/Vector.h ../FK/Base.h
shape/D3DXAnimation.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
shape/D3DXAnimation.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
shape/D3DXAnimation.o: ../FK/OpenGL.H ../FK/D3DXData.H ../FK/Matrix.h
shape/D3DXAnimation.o: ../FK/Angle.h ../FK/Quaternion.h ../FK/Tree.h
shape/D3DXAnimation.o: ../FK/D3DXShapeParser.H ../FK/Texture.h ../FK/Image.h
shape/D3DXAnimation.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/BVHMotion.h
shape/D3DXAnimation.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
shape/D3DXAnimation.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/Math.h
shape/D3DXAnimation.o: ../FK/Error.H
shape/D3DXData.o: ../FK/D3DXData.H ../FK/Matrix.h ../FK/Vector.h ../FK/Base.h
shape/D3DXData.o: ../FK/Angle.h ../FK/Quaternion.h ../FK/Tree.h ../FK/Math.h
shape/D3DXParser.o: ../FK/D3DXParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/D3DXParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/D3DXParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/D3DXParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/D3DXData.H
shape/D3DXParser.o: ../FK/Matrix.h ../FK/Angle.h ../FK/Quaternion.h
shape/D3DXParser.o: ../FK/Tree.h ../FK/D3DXAnimation.H
shape/D3DXParser.o: ../FK/D3DXShapeParser.H ../FK/Texture.h ../FK/Image.h
shape/D3DXParser.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/IFSTexture.h
shape/D3DXParser.o: ../FK/Error.H
shape/D3DXShapeParser.o: ../FK/D3DXShapeParser.H ../FK/ParserBase.H
shape/D3DXShapeParser.o: ../FK/ParserData.h ../FK/Vector.h ../FK/Base.h
shape/D3DXShapeParser.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
shape/D3DXShapeParser.o: ../FK/Color.h ../FK/Attribute.h
shape/D3DXShapeParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Tree.h
shape/D3DXShapeParser.o: ../FK/Matrix.h ../FK/Angle.h ../FK/Texture.h
shape/D3DXShapeParser.o: ../FK/Image.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/D3DXShapeParser.o: ../FK/D3DXData.H ../FK/Quaternion.h
shape/D3DXShapeParser.o: ../FK/IFSTexture.h ../FK/Error.H
shape/DXFParser.o: ../FK/DXFParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/DXFParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/DXFParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/DXFParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/HeapBase.h
shape/DXFParser.o: ../FK/Error.H
shape/EdgePair.o: ../FK/EdgePair.H
shape/Gregory.o: ../FK/Gregory.h ../FK/Surface.h ../FK/Vector.h ../FK/Base.h
shape/Gregory.o: ../FK/FVecArray.h ../FK/Line.h ../FK/LineBase.H
shape/Gregory.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h ../FK/Color.h
shape/Gregory.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/OpenGL.H
shape/Gregory.o: ../FK/Point.h ../FK/Array.H ../FK/IDAdmin.H ../FK/Math.h
shape/Gregory.o: ../FK/Quaternion.h ../FK/Angle.h ../FK/Matrix.h
shape/Gregory.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Window.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Group.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Widget.H
shape/Gregory.o: ../MacPack/include/FL/Enumerations.H
shape/Gregory.o: ../MacPack/include/FL/abi-version.h
shape/Gregory.o: ../MacPack/include/FL/Fl_Export.H
shape/Gregory.o: ../MacPack/include/FL/fl_types.h
shape/Gregory.o: ../MacPack/include/FL/Fl_Bitmap.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Image.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Multi_Browser.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Browser.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Browser_.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Scrollbar.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Slider.H
shape/Gregory.o: ../MacPack/include/FL/Fl_Valuator.H
shape/Gregory.o: ../MacPack/include/FL/Fl.H ../MacPack/include/FL/Fl_Export.H
shape/Gregory.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H ../FK/Image.h
shape/Gregory.o: ../FK/DList.h ../FK/Projection.h ../FK/Model.h
shape/Gregory.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
shape/Gregory.o: ../FK/RenderState.h ../FK/IndexFace.h ../FK/ParserBase.H
shape/Gregory.o: ../FK/ParserData.h ../FK/Texture.h ../FK/Tree.h
shape/Gregory.o: ../FK/Light.h ../FK/FrameController.h ../FK/Plane.h
shape/HRCParser.o: ../FK/HRCParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/HRCParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/HRCParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/HRCParser.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/IndexFace.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/Vector.h
shape/IndexFace.o: ../FK/Base.h ../FK/ParserBase.H ../FK/ParserData.h
shape/IndexFace.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
shape/IndexFace.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
shape/IndexFace.o: ../FK/OpenGL.H ../FK/EdgePair.H ../FK/Solid.h
shape/IndexFace.o: ../FK/SolidBase.h ../FK/Modify.h ../FK/Operation.h
shape/IndexFace.o: ../FK/DrawCache.h ../FK/Reference.h ../FK/Edge.h
shape/IndexFace.o: ../FK/Topology.h ../FK/DataBase.H ../FK/IDAdmin.H
shape/IndexFace.o: ../FK/DataAccess.h ../FK/History.H ../FK/Command.H
shape/IndexFace.o: ../FK/D3DXAnimation.H ../FK/D3DXParser.H ../FK/SMFParser.H
shape/IndexFace.o: ../FK/STLParser.H ../FK/HRCParser.H ../FK/RDSParser.H
shape/IndexFace.o: ../FK/HeapBase.h ../FK/DXFParser.H ../FK/VRMLParser.H
shape/IndexFace.o: ../FK/MQOParser.H ../FK/Texture.h ../FK/Image.h
shape/IndexFace.o: ../FK/VRMLOut.H ../FK/STLOut.H ../FK/DXFOut.H
shape/IndexFace.o: ../FK/MQOOut.H ../FK/IFSetHandle.H ../FK/Error.H
shape/IndexFace.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Window.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Group.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Widget.H
shape/IndexFace.o: ../MacPack/include/FL/Enumerations.H
shape/IndexFace.o: ../MacPack/include/FL/abi-version.h
shape/IndexFace.o: ../MacPack/include/FL/Fl_Export.H
shape/IndexFace.o: ../MacPack/include/FL/fl_types.h
shape/IndexFace.o: ../MacPack/include/FL/Fl_Bitmap.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Image.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Multi_Browser.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Browser.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Browser_.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Scrollbar.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Slider.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Valuator.H
shape/IndexFace.o: ../MacPack/include/FL/Fl.H
shape/IndexFace.o: ../MacPack/include/FL/Fl_Export.H
shape/IndexFace.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
shape/IndexFace.o: ../FK/Matrix.h ../FK/Angle.h ../FK/DList.h
shape/IndexFace.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
shape/IndexFace.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
shape/IndexFace.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/Tree.h
shape/IndexFace.o: ../FK/Light.h ../FK/FrameController.h
shape/Light.o: ../FK/Light.h ../FK/Shape.h ../FK/Base.h ../FK/Palette.h
shape/Light.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Light.o: ../FK/AttributeData.H ../FK/Vector.h ../FK/OpenGL.H
shape/Light.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Angle.h ../FK/Matrix.h
shape/Line.o: ../FK/Line.h ../FK/LineBase.H ../FK/FVecArray.h ../FK/Vector.h
shape/Line.o: ../FK/Base.h ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
shape/Line.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
shape/Line.o: ../FK/OpenGL.H
shape/LineBase.o: ../FK/LineBase.H ../FK/FVecArray.h ../FK/Vector.h
shape/LineBase.o: ../FK/Base.h ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
shape/LineBase.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
shape/LineBase.o: ../FK/OpenGL.H
shape/MQOParser.o: ../FK/MQOParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/MQOParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/MQOParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/MQOParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Texture.h
shape/MQOParser.o: ../FK/Image.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/MQOParser.o: ../FK/MeshTexture.h ../FK/IFSTexture.h ../FK/Tree.h
shape/ParserBase.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Vector.h
shape/ParserBase.o: ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/ParserBase.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/ParserBase.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Particle.o: ../FK/Particle.h ../FK/Base.h ../FK/Vector.h
shape/Particle.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Particle.o: ../FK/AttributeData.H ../FK/Point.h ../FK/FVecArray.h
shape/Particle.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/Shape.h ../FK/Palette.h
shape/Particle.o: ../FK/OpenGL.H
shape/ParticleSet.o: ../FK/ParticleSet.h ../FK/Particle.h ../FK/Base.h
shape/ParticleSet.o: ../FK/Vector.h ../FK/Material.h ../FK/Color.h
shape/ParticleSet.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/IDAdmin.H
shape/ParticleSet.o: ../FK/Point.h ../FK/FVecArray.h ../FK/Array.H
shape/ParticleSet.o: ../FK/Shape.h ../FK/Palette.h ../FK/OpenGL.H
shape/Point.o: ../FK/Point.h ../FK/FVecArray.h ../FK/Vector.h ../FK/Base.h
shape/Point.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/Shape.h ../FK/Palette.h
shape/Point.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Point.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Polygon.o: ../FK/Polygon.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/Polygon.o: ../FK/Vector.h ../FK/Base.h ../FK/ParserBase.H
shape/Polygon.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Palette.h
shape/Polygon.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Polygon.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Polyline.o: ../FK/Polyline.h ../FK/LineBase.H ../FK/FVecArray.h
shape/Polyline.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/Polyline.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Polyline.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Prism.o: ../FK/Prism.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/Prism.o: ../FK/Vector.h ../FK/Base.h ../FK/ParserBase.H
shape/Prism.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Palette.h
shape/Prism.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Prism.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/RBezCurve.o: ../FK/RBezCurve.h ../FK/Curve.h ../FK/Vector.h
shape/RBezCurve.o: ../FK/Base.h ../FK/FVecArray.h ../FK/Line.h
shape/RBezCurve.o: ../FK/LineBase.H ../FK/Shape.h ../FK/Palette.h
shape/RBezCurve.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/RBezCurve.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Point.h
shape/RBezCurve.o: ../FK/Array.H ../FK/IDAdmin.H ../FK/Matrix.h ../FK/Angle.h
shape/RBezCurve.o: ../FK/Math.h ../FK/Quaternion.h ../FK/Error.H
shape/RDSParser.o: ../FK/RDSParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/RDSParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/RDSParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/RDSParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/HeapBase.h
shape/SMFParser.o: ../FK/SMFParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/SMFParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/SMFParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/SMFParser.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/SRFParser.o: ../FK/SRFParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/SRFParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/SRFParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/SRFParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/Error.H
shape/STLParser.o: ../FK/STLParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/STLParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/STLParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/STLParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/HeapBase.h
shape/Shape.o: ../FK/Shape.h ../FK/Base.h ../FK/Palette.h ../FK/Material.h
shape/Shape.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
shape/Shape.o: ../FK/Vector.h ../FK/OpenGL.H
shape/Sphere.o: ../FK/Sphere.h ../FK/IndexFace.h ../FK/FVecArray.h
shape/Sphere.o: ../FK/Vector.h ../FK/Base.h ../FK/ParserBase.H
shape/Sphere.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Palette.h
shape/Sphere.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/Sphere.o: ../FK/AttributeData.H ../FK/OpenGL.H
shape/Surface.o: ../FK/Surface.h ../FK/Vector.h ../FK/Base.h
shape/Surface.o: ../FK/FVecArray.h ../FK/Line.h ../FK/LineBase.H
shape/Surface.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h ../FK/Color.h
shape/Surface.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/OpenGL.H
shape/Surface.o: ../FK/Point.h ../FK/Array.H ../FK/IDAdmin.H
shape/VRMLParser.o: ../FK/VRMLParser.H ../FK/ParserBase.H ../FK/ParserData.h
shape/VRMLParser.o: ../FK/Vector.h ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
shape/VRMLParser.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
shape/VRMLParser.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/HeapBase.h
shape/VRMLParser.o: ../FK/Error.H
solid/Command.o: ../FK/Command.H ../FK/Base.h
solid/DXFOut.o: ../FK/Base.h ../FK/DXFOut.H ../FK/Solid.h ../FK/SolidBase.h
solid/DXFOut.o: ../FK/Modify.h ../FK/Operation.h ../FK/DrawCache.h
solid/DXFOut.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
solid/DXFOut.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/DataBase.H
solid/DXFOut.o: ../FK/IDAdmin.H ../FK/DataAccess.h ../FK/ParserData.h
solid/DXFOut.o: ../FK/Vector.h ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
solid/DXFOut.o: ../FK/Color.h ../FK/OpenGL.H ../FK/History.H ../FK/Command.H
solid/DXFOut.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
solid/DXFOut.o: ../FK/Vertex.h ../FK/Loop.h ../FK/Error.H
solid/DataAccess.o: ../FK/DataAccess.h ../FK/ParserData.h ../FK/Vector.h
solid/DataAccess.o: ../FK/Base.h ../FK/Shape.h ../FK/Palette.h
solid/DataAccess.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
solid/DataAccess.o: ../FK/AttributeData.H ../FK/OpenGL.H ../FK/DataBase.H
solid/DataAccess.o: ../FK/IDAdmin.H ../FK/Vertex.h ../FK/Topology.h
solid/DataAccess.o: ../FK/Half.h ../FK/Edge.h ../FK/Loop.h ../FK/Error.H
solid/DataBase.o: ../FK/Base.h ../FK/DataBase.H ../FK/IDAdmin.H ../FK/Error.H
solid/DataBase.o: ../FK/Vertex.h ../FK/Vector.h ../FK/Topology.h
solid/DataBase.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/Half.h
solid/DataBase.o: ../FK/Edge.h ../FK/Loop.h ../FK/ParserBase.H
solid/DataBase.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Palette.h
solid/DataBase.o: ../FK/Material.h ../FK/Color.h ../FK/OpenGL.H
solid/DrawCache.o: ../FK/DrawCache.h ../FK/Reference.h ../FK/Edge.h
solid/DrawCache.o: ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/DrawCache.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/DrawCache.o: ../FK/DataAccess.h ../FK/ParserData.h ../FK/Vector.h
solid/DrawCache.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
solid/DrawCache.o: ../FK/Color.h ../FK/OpenGL.H ../FK/LIAdmin.H
solid/DrawCache.o: ../FK/Vertex.h ../FK/Error.H
solid/Edge.o: ../FK/Edge.h ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/Edge.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/Edge.o: ../FK/Half.h ../FK/Curve.h ../FK/Vector.h ../FK/FVecArray.h
solid/Edge.o: ../FK/Line.h ../FK/LineBase.H ../FK/Shape.h ../FK/Palette.h
solid/Edge.o: ../FK/Material.h ../FK/Color.h ../FK/OpenGL.H ../FK/Point.h
solid/Edge.o: ../FK/Array.H ../FK/Error.H
solid/Half.o: ../FK/Half.h ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/Half.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/Half.o: ../FK/Vertex.h ../FK/Vector.h ../FK/Edge.h ../FK/Loop.h
solid/Half.o: ../FK/Error.H
solid/History.o: ../FK/History.H ../FK/Vector.h ../FK/Base.h ../FK/Command.H
solid/History.o: ../FK/Error.H
solid/IFSetHandle.o: ../FK/IFSetHandle.H ../FK/Vertex.h ../FK/Base.h
solid/IFSetHandle.o: ../FK/Vector.h ../FK/Topology.h ../FK/Attribute.h
solid/IFSetHandle.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/IFSetHandle.o: ../FK/Half.h ../FK/Edge.h ../FK/Loop.h ../FK/Reference.h
solid/IFSetHandle.o: ../FK/DataAccess.h ../FK/ParserData.h ../FK/Shape.h
solid/IFSetHandle.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
solid/IFSetHandle.o: ../FK/OpenGL.H ../FK/Error.H
solid/Loop.o: ../FK/Loop.h ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/Loop.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/Loop.o: ../FK/Vector.h ../FK/Half.h ../FK/Vertex.h ../FK/Math.h
solid/Loop.o: ../FK/Quaternion.h ../FK/Angle.h ../FK/Matrix.h ../FK/Error.H
solid/MQOOut.o: ../FK/MQOOut.H ../FK/Base.h ../FK/Solid.h ../FK/SolidBase.h
solid/MQOOut.o: ../FK/Modify.h ../FK/Operation.h ../FK/DrawCache.h
solid/MQOOut.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
solid/MQOOut.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/DataBase.H
solid/MQOOut.o: ../FK/IDAdmin.H ../FK/DataAccess.h ../FK/ParserData.h
solid/MQOOut.o: ../FK/Vector.h ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
solid/MQOOut.o: ../FK/Color.h ../FK/OpenGL.H ../FK/History.H ../FK/Command.H
solid/MQOOut.o: ../FK/Vertex.h ../FK/Half.h ../FK/Loop.h ../FK/Error.H
solid/MQOOut.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
solid/Modify.o: ../FK/Modify.h ../FK/Operation.h ../FK/DrawCache.h
solid/Modify.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h ../FK/Base.h
solid/Modify.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/DataBase.H
solid/Modify.o: ../FK/IDAdmin.H ../FK/DataAccess.h ../FK/ParserData.h
solid/Modify.o: ../FK/Vector.h ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
solid/Modify.o: ../FK/Color.h ../FK/OpenGL.H ../FK/History.H ../FK/Command.H
solid/Modify.o: ../FK/IFSetHandle.H ../FK/Vertex.h ../FK/Half.h ../FK/Loop.h
solid/Modify.o: ../FK/SubDivision.H ../FK/Math.h ../FK/Quaternion.h
solid/Modify.o: ../FK/Angle.h ../FK/Matrix.h ../FK/Error.H
solid/Operation.o: ../FK/Operation.h ../FK/DrawCache.h ../FK/Reference.h
solid/Operation.o: ../FK/Edge.h ../FK/Topology.h ../FK/Base.h
solid/Operation.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/DataBase.H
solid/Operation.o: ../FK/IDAdmin.H ../FK/DataAccess.h ../FK/ParserData.h
solid/Operation.o: ../FK/Vector.h ../FK/Shape.h ../FK/Palette.h
solid/Operation.o: ../FK/Material.h ../FK/Color.h ../FK/OpenGL.H
solid/Operation.o: ../FK/History.H ../FK/Command.H ../FK/Vertex.h
solid/Operation.o: ../FK/Half.h ../FK/Loop.h ../FK/Error.H
solid/Reference1.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
solid/Reference1.o: ../FK/Base.h ../FK/Attribute.h ../FK/AttributeData.H
solid/Reference1.o: ../FK/DataBase.H ../FK/IDAdmin.H ../FK/DataAccess.h
solid/Reference1.o: ../FK/ParserData.h ../FK/Vector.h ../FK/Shape.h
solid/Reference1.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
solid/Reference1.o: ../FK/OpenGL.H ../FK/Vertex.h ../FK/Half.h ../FK/Loop.h
solid/Reference2.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
solid/Reference2.o: ../FK/Base.h ../FK/Attribute.h ../FK/AttributeData.H
solid/Reference2.o: ../FK/DataBase.H ../FK/IDAdmin.H ../FK/DataAccess.h
solid/Reference2.o: ../FK/ParserData.h ../FK/Vector.h ../FK/Shape.h
solid/Reference2.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
solid/Reference2.o: ../FK/OpenGL.H ../FK/Vertex.h ../FK/Half.h ../FK/Loop.h
solid/Reference3.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
solid/Reference3.o: ../FK/Base.h ../FK/Attribute.h ../FK/AttributeData.H
solid/Reference3.o: ../FK/DataBase.H ../FK/IDAdmin.H ../FK/DataAccess.h
solid/Reference3.o: ../FK/ParserData.h ../FK/Vector.h ../FK/Shape.h
solid/Reference3.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
solid/Reference3.o: ../FK/OpenGL.H ../FK/Vertex.h ../FK/Half.h ../FK/Loop.h
solid/STLOut.o: ../FK/STLOut.H ../FK/Base.h ../FK/Solid.h ../FK/SolidBase.h
solid/STLOut.o: ../FK/Modify.h ../FK/Operation.h ../FK/DrawCache.h
solid/STLOut.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
solid/STLOut.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/DataBase.H
solid/STLOut.o: ../FK/IDAdmin.H ../FK/DataAccess.h ../FK/ParserData.h
solid/STLOut.o: ../FK/Vector.h ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
solid/STLOut.o: ../FK/Color.h ../FK/OpenGL.H ../FK/History.H ../FK/Command.H
solid/STLOut.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
solid/STLOut.o: ../FK/Vertex.h ../FK/Loop.h ../FK/Error.H
solid/Solid.o: ../FK/Solid.h ../FK/SolidBase.h ../FK/Modify.h
solid/Solid.o: ../FK/Operation.h ../FK/DrawCache.h ../FK/Reference.h
solid/Solid.o: ../FK/Edge.h ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/Solid.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/Solid.o: ../FK/DataAccess.h ../FK/ParserData.h ../FK/Vector.h
solid/Solid.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h ../FK/Color.h
solid/Solid.o: ../FK/OpenGL.H ../FK/History.H ../FK/Command.H
solid/Solid.o: ../FK/SMFParser.H ../FK/ParserBase.H ../FK/SRFParser.H
solid/Solid.o: ../FK/STLParser.H ../FK/HRCParser.H ../FK/RDSParser.H
solid/Solid.o: ../FK/HeapBase.h ../FK/DXFParser.H ../FK/VRMLParser.H
solid/Solid.o: ../FK/MQOParser.H ../FK/Texture.h ../FK/Image.h
solid/Solid.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/D3DXParser.H
solid/Solid.o: ../FK/VRMLOut.H ../FK/STLOut.H ../FK/DXFOut.H ../FK/MQOOut.H
solid/SolidBase.o: ../FK/SolidBase.h ../FK/Modify.h ../FK/Operation.h
solid/SolidBase.o: ../FK/DrawCache.h ../FK/Reference.h ../FK/Edge.h
solid/SolidBase.o: ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/SolidBase.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/SolidBase.o: ../FK/DataAccess.h ../FK/ParserData.h ../FK/Vector.h
solid/SolidBase.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
solid/SolidBase.o: ../FK/Color.h ../FK/OpenGL.H ../FK/History.H
solid/SolidBase.o: ../FK/Command.H ../FK/IndexFace.h ../FK/FVecArray.h
solid/SolidBase.o: ../FK/ParserBase.H ../FK/IFSetHandle.H ../FK/Loop.h
solid/SubDivision.o: ../FK/SubDivision.H ../FK/Modify.h ../FK/Operation.h
solid/SubDivision.o: ../FK/DrawCache.h ../FK/Reference.h ../FK/Edge.h
solid/SubDivision.o: ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/SubDivision.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/SubDivision.o: ../FK/DataAccess.h ../FK/ParserData.h ../FK/Vector.h
solid/SubDivision.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
solid/SubDivision.o: ../FK/Color.h ../FK/OpenGL.H ../FK/History.H
solid/SubDivision.o: ../FK/Command.H ../FK/Loop.h ../FK/Half.h ../FK/Vertex.h
solid/Topology.o: ../FK/Topology.h ../FK/Base.h ../FK/Attribute.h
solid/Topology.o: ../FK/AttributeData.H ../FK/DataBase.H ../FK/IDAdmin.H
solid/VRMLOut.o: ../FK/VRMLOut.H ../FK/Base.h ../FK/Vector.h ../FK/Vertex.h
solid/VRMLOut.o: ../FK/Topology.h ../FK/Attribute.h ../FK/AttributeData.H
solid/VRMLOut.o: ../FK/DataBase.H ../FK/IDAdmin.H ../FK/Loop.h ../FK/Solid.h
solid/VRMLOut.o: ../FK/SolidBase.h ../FK/Modify.h ../FK/Operation.h
solid/VRMLOut.o: ../FK/DrawCache.h ../FK/Reference.h ../FK/Edge.h
solid/VRMLOut.o: ../FK/DataAccess.h ../FK/ParserData.h ../FK/Shape.h
solid/VRMLOut.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
solid/VRMLOut.o: ../FK/OpenGL.H ../FK/History.H ../FK/Command.H
solid/VRMLOut.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
solid/VRMLOut.o: ../FK/Error.H
solid/Vertex.o: ../FK/Vertex.h ../FK/Base.h ../FK/Vector.h ../FK/Topology.h
solid/Vertex.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/DataBase.H
solid/Vertex.o: ../FK/IDAdmin.H ../FK/Half.h ../FK/Loop.h ../FK/Edge.h
solid/Vertex.o: ../FK/Error.H
texture/IFSTexture.o: ../FK/IFSTexture.h ../FK/Texture.h ../FK/Shape.h
texture/IFSTexture.o: ../FK/Base.h ../FK/Palette.h ../FK/Material.h
texture/IFSTexture.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
texture/IFSTexture.o: ../FK/Vector.h ../FK/OpenGL.H ../FK/Image.h
texture/IFSTexture.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
texture/IFSTexture.o: ../FK/ParserData.h ../FK/MQOParser.H ../FK/D3DXParser.H
texture/IFSTexture.o: ../FK/Error.H ../FK/Window.h
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Gl_Window.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Window.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Group.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Widget.H
texture/IFSTexture.o: ../MacPack/include/FL/Enumerations.H
texture/IFSTexture.o: ../MacPack/include/FL/abi-version.h
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Export.H
texture/IFSTexture.o: ../MacPack/include/FL/fl_types.h
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Bitmap.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Image.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Multi_Browser.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Browser.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Browser_.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Scrollbar.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Slider.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Valuator.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl.H
texture/IFSTexture.o: ../MacPack/include/FL/Fl_Export.H
texture/IFSTexture.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
texture/IFSTexture.o: ../FK/Matrix.h ../FK/Angle.h ../FK/DList.h
texture/IFSTexture.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
texture/IFSTexture.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
texture/IFSTexture.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/Tree.h
texture/IFSTexture.o: ../FK/Light.h ../FK/FrameController.h
texture/Image.o: ../FK/Image.h ../FK/Base.h ../FK/Material.h ../FK/Color.h
texture/Image.o: ../FK/OpenGL.H ../FK/TextureDraw.H ../FK/DrawBase.H
texture/Image.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h ../FK/Light.h
texture/Image.o: ../FK/Shape.h ../FK/Palette.h ../FK/Attribute.h
texture/Image.o: ../FK/AttributeData.H ../FK/ShaderBinder.h ../FK/AppWindow.h
texture/Image.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
texture/Image.o: ../MacPack/include/FL/Fl_Window.H
texture/Image.o: ../MacPack/include/FL/Fl_Group.H
texture/Image.o: ../MacPack/include/FL/Fl_Widget.H
texture/Image.o: ../MacPack/include/FL/Enumerations.H
texture/Image.o: ../MacPack/include/FL/abi-version.h
texture/Image.o: ../MacPack/include/FL/Fl_Export.H
texture/Image.o: ../MacPack/include/FL/fl_types.h
texture/Image.o: ../MacPack/include/FL/Fl_Bitmap.H
texture/Image.o: ../MacPack/include/FL/Fl_Image.H
texture/Image.o: ../MacPack/include/FL/Fl_Multi_Browser.H
texture/Image.o: ../MacPack/include/FL/Fl_Browser.H
texture/Image.o: ../MacPack/include/FL/Fl_Browser_.H
texture/Image.o: ../MacPack/include/FL/Fl_Scrollbar.H
texture/Image.o: ../MacPack/include/FL/Fl_Slider.H
texture/Image.o: ../MacPack/include/FL/Fl_Valuator.H
texture/Image.o: ../MacPack/include/FL/Fl.H ../MacPack/include/FL/Fl_Export.H
texture/Image.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H ../FK/DList.h
texture/Image.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
texture/Image.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
texture/Image.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/IndexFace.h
texture/Image.o: ../FK/FVecArray.h ../FK/ParserBase.H ../FK/ParserData.h
texture/Image.o: ../FK/Texture.h ../FK/Tree.h ../FK/FrameController.h
texture/Image.o: ../FK/GuideObject.h ../FK/Line.h ../FK/LineBase.H
texture/Image.o: ../FK/TrackBall.h ../FK/MotionCharactor.h ../FK/IFSTexture.h
texture/Image.o: ../FK/Scene.h ../FK/Fog.h ../FK/MotionData.H
texture/Image.o: ../FK/SpriteModel.h ../FK/UniCode.h ../FK/TextImage.h
texture/Image.o: ../FK/RectTexture.h ../FK/Fullscreen.h ../FK/ShaderProgram.h
texture/Image.o: ../FK/ShaderParameter.h
texture/ImageIO.o: ../FK/Image.h ../FK/Base.h ../FK/Material.h ../FK/Color.h
texture/ImageIO.o: ../FK/OpenGL.H ../FK/Error.H ../MacPack/include/png/png.h
texture/ImageIO.o: ../MacPack/include/png/pnglibconf.h
texture/ImageIO.o: ../MacPack/include/png/pngconf.h
texture/ImageIO.o: ../MacPack/include/jpeg/jpeglib.h
texture/ImageIO.o: ../MacPack/include/jpeg/jconfig.h
texture/ImageIO.o: ../MacPack/include/jpeg/jmorecfg.h
texture/MeshTexture.o: ../FK/MeshTexture.h ../FK/Texture.h ../FK/Shape.h
texture/MeshTexture.o: ../FK/Base.h ../FK/Palette.h ../FK/Material.h
texture/MeshTexture.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
texture/MeshTexture.o: ../FK/Vector.h ../FK/OpenGL.H ../FK/Image.h
texture/MeshTexture.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
texture/MeshTexture.o: ../FK/ParserData.h ../FK/MQOParser.H ../FK/Math.h
texture/MeshTexture.o: ../FK/Quaternion.h ../FK/Angle.h ../FK/Matrix.h
texture/MeshTexture.o: ../FK/Error.H
texture/RectTexture.o: ../FK/RectTexture.h ../FK/Texture.h ../FK/Shape.h
texture/RectTexture.o: ../FK/Base.h ../FK/Palette.h ../FK/Material.h
texture/RectTexture.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
texture/RectTexture.o: ../FK/Vector.h ../FK/OpenGL.H ../FK/Image.h
texture/RectTexture.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
texture/RectTexture.o: ../FK/ParserData.h ../FK/Error.H ../FK/Window.h
texture/RectTexture.o: ../MacPack/include/FL/Fl_Gl_Window.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Window.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Group.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Widget.H
texture/RectTexture.o: ../MacPack/include/FL/Enumerations.H
texture/RectTexture.o: ../MacPack/include/FL/abi-version.h
texture/RectTexture.o: ../MacPack/include/FL/Fl_Export.H
texture/RectTexture.o: ../MacPack/include/FL/fl_types.h
texture/RectTexture.o: ../MacPack/include/FL/Fl_Bitmap.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Image.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Multi_Browser.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Browser.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Browser_.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Scrollbar.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Slider.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Valuator.H
texture/RectTexture.o: ../MacPack/include/FL/Fl.H
texture/RectTexture.o: ../MacPack/include/FL/Fl_Export.H
texture/RectTexture.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
texture/RectTexture.o: ../FK/Matrix.h ../FK/Angle.h ../FK/DList.h
texture/RectTexture.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
texture/RectTexture.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
texture/RectTexture.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/Tree.h
texture/RectTexture.o: ../FK/Light.h ../FK/FrameController.h
texture/TextImage.o: ../FK/TextImage.h ../FK/Image.h ../FK/Base.h
texture/TextImage.o: ../FK/Material.h ../FK/Color.h ../FK/OpenGL.H
texture/TextImage.o: ../FK/UniCode.h ../FK/Error.H
texture/TextImage.o: ../MacPack/include/ft2build.h
texture/TextImage.o: ../MacPack/include/freetype/config/ftheader.h
texture/TextImage.o: ../MacPack/include/freetype/freetype.h
texture/TextImage.o: ../MacPack/include/freetype/config/ftconfig.h
texture/TextImage.o: ../MacPack/include/freetype/config/ftoption.h
texture/TextImage.o: ../MacPack/include/freetype/config/ftstdlib.h
texture/TextImage.o: ../MacPack/include/freetype/fttypes.h
texture/TextImage.o: ../MacPack/include/freetype/config/ftconfig.h
texture/TextImage.o: ../MacPack/include/freetype/ftsystem.h
texture/TextImage.o: ../MacPack/include/freetype/ftimage.h
texture/TextImage.o: ../MacPack/include/freetype/fterrors.h
texture/TextImage.o: ../MacPack/include/freetype/ftmoderr.h
texture/TextImage.o: ../MacPack/include/freetype/fterrdef.h
texture/TextImage.o: ../MacPack/include/freetype/ftglyph.h
texture/TextImage.o: ../MacPack/include/freetype/freetype.h
texture/TextImage.o: ../MacPack/include/freetype/ftoutln.h
texture/Texture.o: ../FK/Texture.h ../FK/Shape.h ../FK/Base.h ../FK/Palette.h
texture/Texture.o: ../FK/Material.h ../FK/Color.h ../FK/Attribute.h
texture/Texture.o: ../FK/AttributeData.H ../FK/Vector.h ../FK/OpenGL.H
texture/Texture.o: ../FK/Image.h ../FK/IndexFace.h ../FK/FVecArray.h
texture/Texture.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Error.H
texture/Texture.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
texture/Texture.o: ../MacPack/include/FL/Fl_Window.H
texture/Texture.o: ../MacPack/include/FL/Fl_Group.H
texture/Texture.o: ../MacPack/include/FL/Fl_Widget.H
texture/Texture.o: ../MacPack/include/FL/Enumerations.H
texture/Texture.o: ../MacPack/include/FL/abi-version.h
texture/Texture.o: ../MacPack/include/FL/Fl_Export.H
texture/Texture.o: ../MacPack/include/FL/fl_types.h
texture/Texture.o: ../MacPack/include/FL/Fl_Bitmap.H
texture/Texture.o: ../MacPack/include/FL/Fl_Image.H
texture/Texture.o: ../MacPack/include/FL/Fl_Multi_Browser.H
texture/Texture.o: ../MacPack/include/FL/Fl_Browser.H
texture/Texture.o: ../MacPack/include/FL/Fl_Browser_.H
texture/Texture.o: ../MacPack/include/FL/Fl_Scrollbar.H
texture/Texture.o: ../MacPack/include/FL/Fl_Slider.H
texture/Texture.o: ../MacPack/include/FL/Fl_Valuator.H
texture/Texture.o: ../MacPack/include/FL/Fl.H
texture/Texture.o: ../MacPack/include/FL/Fl_Export.H
texture/Texture.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
texture/Texture.o: ../FK/Matrix.h ../FK/Angle.h ../FK/DList.h
texture/Texture.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
texture/Texture.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
texture/Texture.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/Tree.h
texture/Texture.o: ../FK/Light.h ../FK/FrameController.h
texture/TriTexture.o: ../FK/TriTexture.h ../FK/Texture.h ../FK/Shape.h
texture/TriTexture.o: ../FK/Base.h ../FK/Palette.h ../FK/Material.h
texture/TriTexture.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
texture/TriTexture.o: ../FK/Vector.h ../FK/OpenGL.H ../FK/Image.h
texture/TriTexture.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
texture/TriTexture.o: ../FK/ParserData.h ../FK/Error.H ../FK/Window.h
texture/TriTexture.o: ../MacPack/include/FL/Fl_Gl_Window.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Window.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Group.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Widget.H
texture/TriTexture.o: ../MacPack/include/FL/Enumerations.H
texture/TriTexture.o: ../MacPack/include/FL/abi-version.h
texture/TriTexture.o: ../MacPack/include/FL/Fl_Export.H
texture/TriTexture.o: ../MacPack/include/FL/fl_types.h
texture/TriTexture.o: ../MacPack/include/FL/Fl_Bitmap.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Image.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Multi_Browser.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Browser.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Browser_.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Scrollbar.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Slider.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Valuator.H
texture/TriTexture.o: ../MacPack/include/FL/Fl.H
texture/TriTexture.o: ../MacPack/include/FL/Fl_Export.H
texture/TriTexture.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
texture/TriTexture.o: ../FK/Matrix.h ../FK/Angle.h ../FK/DList.h
texture/TriTexture.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
texture/TriTexture.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
texture/TriTexture.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/Tree.h
texture/TriTexture.o: ../FK/Light.h ../FK/FrameController.h
texture/UniCode.o: ../FK/UniCode.h ../FK/Base.h ../FK/Error.H
texture/UniCode.o: ../MacPack/include/iconv.h
util/AppWindow.o: ../FK/AppWindow.h ../FK/Window.h
util/AppWindow.o: ../MacPack/include/FL/Fl_Gl_Window.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Window.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Group.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Widget.H
util/AppWindow.o: ../MacPack/include/FL/Enumerations.H
util/AppWindow.o: ../MacPack/include/FL/abi-version.h
util/AppWindow.o: ../MacPack/include/FL/Fl_Export.H
util/AppWindow.o: ../MacPack/include/FL/fl_types.h
util/AppWindow.o: ../MacPack/include/FL/Fl_Bitmap.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Image.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Multi_Browser.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Browser.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Browser_.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Scrollbar.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Slider.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Valuator.H
util/AppWindow.o: ../MacPack/include/FL/Fl.H
util/AppWindow.o: ../MacPack/include/FL/Fl_Export.H
util/AppWindow.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H ../FK/Base.h
util/AppWindow.o: ../FK/OpenGL.H ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h
util/AppWindow.o: ../FK/Image.h ../FK/Material.h ../FK/Color.h ../FK/DList.h
util/AppWindow.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
util/AppWindow.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
util/AppWindow.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/RenderState.h
util/AppWindow.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
util/AppWindow.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
util/AppWindow.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
util/AppWindow.o: ../FK/Light.h ../FK/FrameController.h ../FK/GuideObject.h
util/AppWindow.o: ../FK/Line.h ../FK/LineBase.H ../FK/TrackBall.h
util/AppWindow.o: ../FK/MotionCharactor.h ../FK/IFSTexture.h ../FK/Scene.h
util/AppWindow.o: ../FK/Fog.h ../FK/MotionData.H ../FK/SpriteModel.h
util/AppWindow.o: ../FK/UniCode.h ../FK/TextImage.h ../FK/RectTexture.h
util/AppWindow.o: ../FK/Fullscreen.h ../MacPack/include/FL/x.H ../FK/System.h
util/AppWindow.o: ../FK/MatExample.h
util/Fullscreen.o: ../FK/Fullscreen.h ../FK/Window.h
util/Fullscreen.o: ../MacPack/include/FL/Fl_Gl_Window.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Window.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Group.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Widget.H
util/Fullscreen.o: ../MacPack/include/FL/Enumerations.H
util/Fullscreen.o: ../MacPack/include/FL/abi-version.h
util/Fullscreen.o: ../MacPack/include/FL/Fl_Export.H
util/Fullscreen.o: ../MacPack/include/FL/fl_types.h
util/Fullscreen.o: ../MacPack/include/FL/Fl_Bitmap.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Image.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Multi_Browser.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Browser.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Browser_.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Scrollbar.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Slider.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Valuator.H
util/Fullscreen.o: ../MacPack/include/FL/Fl.H
util/Fullscreen.o: ../MacPack/include/FL/Fl_Export.H
util/Fullscreen.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
util/Fullscreen.o: ../FK/Base.h ../FK/OpenGL.H ../FK/Matrix.h ../FK/Vector.h
util/Fullscreen.o: ../FK/Angle.h ../FK/Image.h ../FK/Material.h ../FK/Color.h
util/Fullscreen.o: ../FK/DList.h ../FK/Projection.h ../FK/Math.h
util/Fullscreen.o: ../FK/Quaternion.h ../FK/Model.h ../FK/Boundary.h
util/Fullscreen.o: ../FK/MatAdmin.h ../FK/DrawMode.h ../FK/Palette.h
util/Fullscreen.o: ../FK/RenderState.h ../FK/IndexFace.h ../FK/FVecArray.h
util/Fullscreen.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Shape.h
util/Fullscreen.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/Texture.h
util/Fullscreen.o: ../FK/Tree.h ../FK/Light.h ../FK/FrameController.h
util/GuideObject.o: ../FK/GuideObject.h ../FK/Line.h ../FK/LineBase.H
util/GuideObject.o: ../FK/FVecArray.h ../FK/Vector.h ../FK/Base.h
util/GuideObject.o: ../FK/Shape.h ../FK/Palette.h ../FK/Material.h
util/GuideObject.o: ../FK/Color.h ../FK/Attribute.h ../FK/AttributeData.H
util/GuideObject.o: ../FK/OpenGL.H ../FK/Model.h ../FK/Boundary.h
util/GuideObject.o: ../FK/MatAdmin.h ../FK/Matrix.h ../FK/Angle.h
util/GuideObject.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/IndexFace.h
util/GuideObject.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Texture.h
util/GuideObject.o: ../FK/Image.h ../FK/Tree.h ../FK/Scene.h ../FK/Fog.h
util/GuideObject.o: ../FK/DList.h ../FK/Projection.h ../FK/Math.h
util/GuideObject.o: ../FK/Quaternion.h ../FK/Light.h
util/Misc.o: ../FK/Misc.h
util/MotionCharactor.o: ../FK/MotionCharactor.h ../FK/Shape.h ../FK/Base.h
util/MotionCharactor.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
util/MotionCharactor.o: ../FK/Attribute.h ../FK/AttributeData.H
util/MotionCharactor.o: ../FK/Vector.h ../FK/OpenGL.H ../FK/IFSTexture.h
util/MotionCharactor.o: ../FK/Texture.h ../FK/Image.h ../FK/IndexFace.h
util/MotionCharactor.o: ../FK/FVecArray.h ../FK/ParserBase.H
util/MotionCharactor.o: ../FK/ParserData.h ../FK/Scene.h ../FK/Fog.h
util/MotionCharactor.o: ../FK/DList.h ../FK/Projection.h ../FK/Matrix.h
util/MotionCharactor.o: ../FK/Angle.h ../FK/Math.h ../FK/Quaternion.h
util/MotionCharactor.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
util/MotionCharactor.o: ../FK/DrawMode.h ../FK/RenderState.h ../FK/Tree.h
util/MotionCharactor.o: ../FK/Light.h ../FK/MotionData.H ../FK/Error.H
util/MotionData.o: ../FK/MotionData.H ../FK/Quaternion.h ../FK/Vector.h
util/MotionData.o: ../FK/Base.h ../FK/Angle.h ../FK/Matrix.h ../FK/Model.h
util/MotionData.o: ../FK/Boundary.h ../FK/MatAdmin.h ../FK/DrawMode.h
util/MotionData.o: ../FK/Palette.h ../FK/Material.h ../FK/Color.h
util/MotionData.o: ../FK/RenderState.h ../FK/IndexFace.h ../FK/FVecArray.h
util/MotionData.o: ../FK/ParserBase.H ../FK/ParserData.h ../FK/Shape.h
util/MotionData.o: ../FK/Attribute.h ../FK/AttributeData.H ../FK/OpenGL.H
util/MotionData.o: ../FK/Texture.h ../FK/Image.h ../FK/Tree.h ../FK/Math.h
util/SpriteModel.o: ../FK/SpriteModel.h ../FK/UniCode.h ../FK/Base.h
util/SpriteModel.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
util/SpriteModel.o: ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h
util/SpriteModel.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/Material.h
util/SpriteModel.o: ../FK/Color.h ../FK/RenderState.h ../FK/IndexFace.h
util/SpriteModel.o: ../FK/FVecArray.h ../FK/ParserBase.H ../FK/ParserData.h
util/SpriteModel.o: ../FK/Shape.h ../FK/Attribute.h ../FK/AttributeData.H
util/SpriteModel.o: ../FK/OpenGL.H ../FK/Texture.h ../FK/Image.h ../FK/Tree.h
util/SpriteModel.o: ../FK/TextImage.h ../FK/RectTexture.h ../FK/Scene.h
util/SpriteModel.o: ../FK/Fog.h ../FK/DList.h ../FK/Projection.h ../FK/Math.h
util/SpriteModel.o: ../FK/Quaternion.h ../FK/Light.h ../FK/Window.h
util/SpriteModel.o: ../MacPack/include/FL/Fl_Gl_Window.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Window.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Group.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Widget.H
util/SpriteModel.o: ../MacPack/include/FL/Enumerations.H
util/SpriteModel.o: ../MacPack/include/FL/abi-version.h
util/SpriteModel.o: ../MacPack/include/FL/Fl_Export.H
util/SpriteModel.o: ../MacPack/include/FL/fl_types.h
util/SpriteModel.o: ../MacPack/include/FL/Fl_Bitmap.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Image.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Multi_Browser.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Browser.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Browser_.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Scrollbar.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Slider.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Valuator.H
util/SpriteModel.o: ../MacPack/include/FL/Fl.H
util/SpriteModel.o: ../MacPack/include/FL/Fl_Export.H
util/SpriteModel.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
util/SpriteModel.o: ../FK/FrameController.h
util/TrackBall.o: ../FK/TrackBall.h ../FK/Window.h
util/TrackBall.o: ../MacPack/include/FL/Fl_Gl_Window.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Window.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Group.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Widget.H
util/TrackBall.o: ../MacPack/include/FL/Enumerations.H
util/TrackBall.o: ../MacPack/include/FL/abi-version.h
util/TrackBall.o: ../MacPack/include/FL/Fl_Export.H
util/TrackBall.o: ../MacPack/include/FL/fl_types.h
util/TrackBall.o: ../MacPack/include/FL/Fl_Bitmap.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Image.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Multi_Browser.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Browser.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Browser_.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Scrollbar.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Slider.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Valuator.H
util/TrackBall.o: ../MacPack/include/FL/Fl.H
util/TrackBall.o: ../MacPack/include/FL/Fl_Export.H
util/TrackBall.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H ../FK/Base.h
util/TrackBall.o: ../FK/OpenGL.H ../FK/Matrix.h ../FK/Vector.h ../FK/Angle.h
util/TrackBall.o: ../FK/Image.h ../FK/Material.h ../FK/Color.h ../FK/DList.h
util/TrackBall.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
util/TrackBall.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
util/TrackBall.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/RenderState.h
util/TrackBall.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
util/TrackBall.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
util/TrackBall.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
util/TrackBall.o: ../FK/Light.h ../FK/FrameController.h
window/ShapeViewer_fltk.o: ../FK/ShapeViewer.h ../FK/Window.h
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Gl_Window.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Window.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Group.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Widget.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Enumerations.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/abi-version.h
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Export.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/fl_types.h
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Bitmap.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Image.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Multi_Browser.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Browser.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Browser_.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Scrollbar.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Slider.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Valuator.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Export.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
window/ShapeViewer_fltk.o: ../FK/Base.h ../FK/OpenGL.H ../FK/Matrix.h
window/ShapeViewer_fltk.o: ../FK/Vector.h ../FK/Angle.h ../FK/Image.h
window/ShapeViewer_fltk.o: ../FK/Material.h ../FK/Color.h ../FK/DList.h
window/ShapeViewer_fltk.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
window/ShapeViewer_fltk.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
window/ShapeViewer_fltk.o: ../FK/DrawMode.h ../FK/Palette.h
window/ShapeViewer_fltk.o: ../FK/RenderState.h ../FK/IndexFace.h
window/ShapeViewer_fltk.o: ../FK/FVecArray.h ../FK/ParserBase.H
window/ShapeViewer_fltk.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
window/ShapeViewer_fltk.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
window/ShapeViewer_fltk.o: ../FK/Light.h ../FK/FrameController.h
window/ShapeViewer_fltk.o: ../FK/MatExample.h ../FK/Line.h ../FK/LineBase.H
window/ShapeViewer_fltk.o: ../FK/Solid.h ../FK/SolidBase.h ../FK/Modify.h
window/ShapeViewer_fltk.o: ../FK/Operation.h ../FK/DrawCache.h
window/ShapeViewer_fltk.o: ../FK/Reference.h ../FK/Edge.h ../FK/Topology.h
window/ShapeViewer_fltk.o: ../FK/DataBase.H ../FK/IDAdmin.H
window/ShapeViewer_fltk.o: ../FK/DataAccess.h ../FK/History.H ../FK/Command.H
window/ShapeViewer_fltk.o: ../FK/Scene.h ../FK/Fog.h ../FK/Vertex.h
window/ShapeViewer_fltk.o: ../FK/Error.H ../FK/System.h
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Menu_Bar.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Menu_.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Menu_Item.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Value_Slider.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Roller.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Group.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Check_Button.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Light_Button.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Button.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Color_Chooser.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Box.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Return_Button.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Choice.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Value_Input.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Input.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Input_.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/fl_ask.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Native_File_Chooser.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_File_Chooser.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Double_Window.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Menu_Button.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Button.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Preferences.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Tile.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_File_Browser.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_File_Icon.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/filename.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_File_Input.H
window/ShapeViewer_fltk.o: ../MacPack/include/FL/Fl_Input.H
window/WindowEvent_fltk.o: ../FK/Window.h
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Gl_Window.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Window.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Group.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Widget.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Enumerations.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/abi-version.h
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Export.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/fl_types.h
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Bitmap.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Image.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Multi_Browser.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Browser.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Browser_.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Scrollbar.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Slider.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Valuator.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/Fl_Export.H
window/WindowEvent_fltk.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
window/WindowEvent_fltk.o: ../FK/Base.h ../FK/OpenGL.H ../FK/Matrix.h
window/WindowEvent_fltk.o: ../FK/Vector.h ../FK/Angle.h ../FK/Image.h
window/WindowEvent_fltk.o: ../FK/Material.h ../FK/Color.h ../FK/DList.h
window/WindowEvent_fltk.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
window/WindowEvent_fltk.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
window/WindowEvent_fltk.o: ../FK/DrawMode.h ../FK/Palette.h
window/WindowEvent_fltk.o: ../FK/RenderState.h ../FK/IndexFace.h
window/WindowEvent_fltk.o: ../FK/FVecArray.h ../FK/ParserBase.H
window/WindowEvent_fltk.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
window/WindowEvent_fltk.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
window/WindowEvent_fltk.o: ../FK/Light.h ../FK/FrameController.h
window/WindowEvent_fltk.o: ../FK/Error.H
window/Window_fltk.o: ../FK/Window.h ../MacPack/include/FL/Fl_Gl_Window.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Window.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Group.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Widget.H
window/Window_fltk.o: ../MacPack/include/FL/Enumerations.H
window/Window_fltk.o: ../MacPack/include/FL/abi-version.h
window/Window_fltk.o: ../MacPack/include/FL/Fl_Export.H
window/Window_fltk.o: ../MacPack/include/FL/fl_types.h
window/Window_fltk.o: ../MacPack/include/FL/Fl_Bitmap.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Image.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Multi_Browser.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Browser.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Browser_.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Scrollbar.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Slider.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Valuator.H
window/Window_fltk.o: ../MacPack/include/FL/Fl.H
window/Window_fltk.o: ../MacPack/include/FL/Fl_Export.H
window/Window_fltk.o: ../MacPack/include/FL/fl_utf8.h ../FK/Engine.H
window/Window_fltk.o: ../FK/Base.h ../FK/OpenGL.H ../FK/Matrix.h
window/Window_fltk.o: ../FK/Vector.h ../FK/Angle.h ../FK/Image.h
window/Window_fltk.o: ../FK/Material.h ../FK/Color.h ../FK/DList.h
window/Window_fltk.o: ../FK/Projection.h ../FK/Math.h ../FK/Quaternion.h
window/Window_fltk.o: ../FK/Model.h ../FK/Boundary.h ../FK/MatAdmin.h
window/Window_fltk.o: ../FK/DrawMode.h ../FK/Palette.h ../FK/RenderState.h
window/Window_fltk.o: ../FK/IndexFace.h ../FK/FVecArray.h ../FK/ParserBase.H
window/Window_fltk.o: ../FK/ParserData.h ../FK/Shape.h ../FK/Attribute.h
window/Window_fltk.o: ../FK/AttributeData.H ../FK/Texture.h ../FK/Tree.h
window/Window_fltk.o: ../FK/Light.h ../FK/FrameController.h ../FK/Error.H
window/Window_fltk.o: ../MacPack/include/FL/x.H
window/Window_fltk.o: ../MacPack/include/FL/fl_ask.H
