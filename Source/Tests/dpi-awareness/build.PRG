*========================================================================================
* Builds a project into an exe
*========================================================================================
LParameter tcMainFile

	Local lcProject
	Set SAFETY off
	lcProject = ;
		JustDrive (m.tcMainFile) + Addbs (JustPath (m.tcMainFile)) + ;
		StrExtract(JustStem (m.tcMainFile), "", "_main")
	Build Project (m.lcProject) from (m.tcMainFile)
	Build Exe (m.lcProject) from (m.lcProject)
	quit
