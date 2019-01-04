#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batchname_cannot_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batchname_cannot_blank() { }
		~CIFast_IFast_ifastdbrkr_err_batchname_cannot_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCHNAME_CANNOT_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch Name can not be blank for search by batch name.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batch Name can not be blank for search by batch name.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch-Name darf bei einer Suche nach Batch-Name nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El nombre de lote no puede estar en blanco para la búsqueda por nombre de lote")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Nom du lot doit être rempli pour une recherche par nom de lot.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batchnaam mag niet leeg zijn voor zoeken op batchnaaam")); }

        // Actions
	};
}



