#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_process_create_fail : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_process_create_fail() { }
		~CBase_Infrastructure_dicore_dicore_process_create_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PROCESS_CREATE_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%GENERIC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check to make sure the .EXE to be run is in the PATH.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check to make sure the .EXE to be run is in the PATH.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Stellen Sie sicher, dass die .EXE-Datei im PFAD ausgeführt wird.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique para asegurarse de que el .EXE que se debe ejecutar está en la RUTA.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez pour vous assurer que le .EXE qui sera exécuté est dans le chemin.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer om ervoor te zorgen dat .EXR wordt uitgevoerd in het PAD")); }
	};
}



