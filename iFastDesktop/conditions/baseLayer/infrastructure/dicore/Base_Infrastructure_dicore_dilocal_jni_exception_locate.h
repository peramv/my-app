#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dilocal_jni_exception_locate : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dilocal_jni_exception_locate() { }
		~CBase_Infrastructure_dicore_dilocal_jni_exception_locate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DILOCAL_JNI_EXCEPTION_LOCATE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("^:Java Exception Occurred in locating ^() method.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^:Java Exception Occurred in locating ^() method.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("^:Java-Ausnahme aufgetreten bei Suche nach ^()-Methode.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("^:Java Exception Occurred in locating ^() method.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("^ : une exception Java s'est produite lors de la localisation de la méthode ^().")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("^:Java-exceptie opgetreden bij opzoeken van ^() methode")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check Java Runtime Environment.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check Java Runtime Environment.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Java-Ausführungsumgebung.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check Java Runtime Environment.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'environnement du moteur d'exécution Java.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de Java Runtime Environment")); }
	};
}



