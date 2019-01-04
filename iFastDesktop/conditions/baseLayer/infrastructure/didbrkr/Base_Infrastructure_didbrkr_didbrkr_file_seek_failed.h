#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_file_seek_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_file_seek_failed() { }
		~CBase_Infrastructure_didbrkr_didbrkr_file_seek_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_FILE_SEEK_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is invalid offset in the repository file.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is invalid offset in the repository file.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt einen ungültigen Offset in der Lagerdatei.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un offset no válido en el archivo de depósito.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a une compensation invalide dans le fichier de référence.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is ongeldige offset in het verzamelbestand")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check repository file.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check repository file.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Repositorydatei.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check repository file.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier de référence.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het verzamelbestand")); }
	};
}



