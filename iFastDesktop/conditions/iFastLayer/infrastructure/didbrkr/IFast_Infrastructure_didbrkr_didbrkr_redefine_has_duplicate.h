#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_redefine_has_duplicate : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_redefine_has_duplicate() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_redefine_has_duplicate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REDEFINE_HAS_DUPLICATE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Element %element% from redefine %redefine% already exists in the Data object.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Element %element% from redefine %redefine% already exists in the Data object.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Element %element% aus der Neudefinition %redefine% existiert bereits im Datenobjekt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El elemento %element% de la redefinición %redefine% ya existe en el objeto de datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'élément %element% de la redéfinition %redefine% existe déjà dans l'objet de données.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Element %element% van nieuwe definitie %redefine% bestaat al in het gegevensobject")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de propiedades.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



