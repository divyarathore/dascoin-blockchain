/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <graphene/chain/protocol/transfer.hpp>

namespace graphene { namespace chain {

share_type transfer_operation::calculate_fee( const fee_parameters_type& schedule )const
{
   share_type core_fee_required = schedule.fee;
   if( memo )
      core_fee_required += calculate_data_fee( fc::raw::pack_size(memo), schedule.price_per_kbyte );
   return core_fee_required;
}

void transfer_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0 );
   FC_ASSERT( from != to );
   FC_ASSERT( amount.amount > 0 );
}

share_type override_transfer_operation::calculate_fee( const fee_parameters_type& schedule )const
{
   share_type core_fee_required = schedule.fee;
   if( memo )
      core_fee_required += calculate_data_fee( fc::raw::pack_size(memo), schedule.price_per_kbyte );
   return core_fee_required;
}

void override_transfer_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0 );
   FC_ASSERT( from != to );
   FC_ASSERT( amount.amount > 0 );
   FC_ASSERT( issuer != from );
}

void transfer_vault_to_wallet_operation::validate() const
{
   FC_ASSERT( fee.amount >= 0 );
   FC_ASSERT( from_vault != to_wallet );
   FC_ASSERT( asset_to_transfer.amount >= 0 );
   FC_ASSERT( reserved_to_transfer >= 0 );
   FC_ASSERT( asset_to_transfer.amount + reserved_to_transfer > 0 );
}

void transfer_wallet_to_vault_operation::validate() const
{
   FC_ASSERT( fee.amount >= 0 );
   FC_ASSERT( from_wallet != to_vault );
   FC_ASSERT( asset_to_transfer.amount >= 0 );
   FC_ASSERT( reserved_to_transfer >= 0 );
   FC_ASSERT( asset_to_transfer.amount + reserved_to_transfer > 0 );
}

void update_euro_limit_operation::validate() const
{
   if ( eur_limit.valid() )
      FC_ASSERT( eur_limit->value > 0 );
   FC_ASSERT( comment.length() > 0 && comment.length() <= DASCOIN_MAX_COMMENT_LENGTH );
}

void remove_vault_limit_operation::validate() const
{
   FC_ASSERT( comment.length() <= DASCOIN_MAX_COMMENT_LENGTH );
}

} } // graphene::chain
