#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_origtransld_must_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_origtransld_must_blank() { }
		~CIFast_IFast_ifastdbrkr_err_origtransld_must_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ORIGTRANSLD_MUST_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Type and Entity Type Sequence must be populated, OrigTransld must be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entity Type and Entity Type Sequence must be populated, OrigTransld must be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt-Typ und Objekt-Typ-Abschnitt müssen ausgefüllt sein, Original-Transaktions-ID muss leer sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben completarse los campos Tipo de entidad y Secuencia de tipo de entidad. Identificación de transacción original debe dejarse en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'entité et la séquence de type d'entité sont requis, mais le champ du code de transaction d'origine doit être vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheidtype en Eeenheidtypevolgorde moeten worden ingevuld, Origineel transactie-ID moet leeg blijven")); }

        // Actions
	};
}



