﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_not_a_dataelement_object : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_not_a_dataelement_object() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_not_a_dataelement_object() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_NOT_A_DATAELEMENT_OBJECT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Component %comp% is not a DataElement object.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Component %comp% is not a DataElement object.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Komponente %comp% ist kein Datenelement-Objekt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El componente %comp% no es un objeto de elemento de datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La composante %comp% n'est pas un objet de l'élément de données.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Component %comp% is geen DataElement-object")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de propiedades")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



