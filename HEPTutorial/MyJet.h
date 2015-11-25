/*
 * MyJet.h
 *
 *  Created on: Feb 1, 2012
 *      Author: csander
 */

#ifndef MYJET_H_
#define MYJET_H_

#include <TLorentzVector.h>
#include <TRandom3.h>

using namespace std;

class MyJet: public TLorentzVector {

   public:

      MyJet();
      MyJet(double px, double py, double pz, double e) {
         SetPxPyPzE(px, py, pz, e);
      }
      ;
      virtual ~MyJet();

      void SetBTagDiscriminator(double x) {
         btag = x;
      }
      ;

      const double GetBTagDiscriminator() {
         return btag;
      }
      ;

      const bool IsBTagged(double th=1.74) {
         return (btag > th);
      }
      ;

      void SetJetID(bool id) {
         jetid = id;
      }
      ;

      const bool GetJetID() {
         return jetid;
      }
      ;

      const string toString() {
         string px = to_string(this->Px());
         string py = to_string(this->Py());
         string pz = to_string(this->Pz());
         string phi = to_string(this->Phi());
         string eta = to_string(this->Eta());
         string bTag = to_string(this->GetBTagDiscriminator());

         return "(" + px + ", " + py + ", " + pz + ") PhiAndEta(" + phi + ", " + eta + ") bTag: " + bTag;
      }


   private:

      double btag;
      bool jetid;

};

#endif /* MYJET_H_ */
