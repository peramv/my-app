#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_available_to_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_available_to_group() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_available_to_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_AVAILABLE_TO_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
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



