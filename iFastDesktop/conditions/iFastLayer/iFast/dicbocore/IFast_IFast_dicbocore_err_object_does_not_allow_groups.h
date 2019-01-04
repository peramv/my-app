#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_object_does_not_allow_groups : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_object_does_not_allow_groups() { }
		~CIFast_IFast_dicbocore_err_object_does_not_allow_groups() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_DOES_NOT_ALLOW_GROUPS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUNDNAME% %CLASS% is not a valid fund/class combination for the group to which this account belongs.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FUNDNAME% %CLASS% n'est pas une combinaison de fonds ou de catégorie valide pour le groupe auquel le fonds appartient.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FUNDNAME% %CLASS% ist keine gültige Fonds/Klassen-Kombination für die Gruppe, zu der das Konto gehört.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FUNDNAME% %CLASS% no es una combinación de fondo/clase válida para el grupo al que pertenece esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUNDNAME% et la classe %CLASS% ne constituent pas une combinaison valide pour le groupe auquel ce compte appartient.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FUNDNAME% %CLASS% is geen geldige fonds/categoriecombinatie voor de groep waartoe dit account behoort")); }

        // Actions
	};
}



