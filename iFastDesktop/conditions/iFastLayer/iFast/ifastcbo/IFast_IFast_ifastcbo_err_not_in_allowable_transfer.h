#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_not_in_allowable_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_not_in_allowable_transfer() { }
		~CIFast_IFast_ifastcbo_err_not_in_allowable_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_IN_ALLOWABLE_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange from fund %FROM_FUND%, class %FROM_CLASS% to fund %TO_FUND%,class %TO_CLASS% is not allowed under the allowable transfer table.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'échange du fonds %FROM_FUND%, catégorie %FROM_CLASS% vers le fonds %TO_FUND%, catégorie %TO_CLASS% n'est pas autorisé par la")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wechseln von Fonds  %FROM_FUND%, Klasse %FROM_CLASS% zu Fonds %TO_FUND%, Klasse %TO_CLASS% im Bereich der erlaubten Transfertabelle ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten traspasos del fondo %FROM_FUND%, clase %FROM_CLASS% al fondo %TO_FUND%,clase %TO_CLASS% conforme a la tabla de transferencias permitidas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un échange du fonds %FROM_FUND% et de la classe %FROM_CLASS% au fonds %TO_FUND% et à la classe %TO_CLASS% n'est pas autorisé dans la table de transfert autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ruilen van fonds %FROM_FUND%, categorie %FROM_CLASS% naar fonds %TO_FUND%, categorie %TO_CLASS% is niet toegestaan volgens de tabel voor toegestane overdrachten")); }

        // Actions
	};
}



