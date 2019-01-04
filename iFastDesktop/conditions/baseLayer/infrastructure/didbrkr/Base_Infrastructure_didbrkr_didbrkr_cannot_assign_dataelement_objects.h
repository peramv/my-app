#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_cannot_assign_dataelement_objects : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_cannot_assign_dataelement_objects() { }
		~CBase_Infrastructure_didbrkr_didbrkr_cannot_assign_dataelement_objects() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_CANNOT_ASSIGN_DATAELEMENT_OBJECTS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not assign DataElement objects, one doesn't have properties.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Could not assign DataElement objects, one doesn't have properties.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenelement-Objekte konnten nicht zugewiesen werden, eines hat keine Eigenschaften.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se pudieron asignar objetos de elementos de datos, uno no tiene propiedades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'attribuer les objets de l'élément de données, l'un d'entre eux n'a aucune propriété.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("DataElement-objecten konden niet worden toegekend, één heeft geen eigenschappen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



