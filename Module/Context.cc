#include "Context.h"
const char tvoid[] = "void";

Context::Context()
{
  cblock = 1;     
  blockmax = 1;   
  decl = 0;       
  func = false;   
  retu = false;   
  ex = 0;         
  proto = false;  
  call = false;
  cc = 0;
  cpos = start;
  minus = false;
  sp = 0;
  gp = 0;
  maxsp = 0;
    
  labelcount=0; 
  startcount.push((unsigned)0);
  startc=0;
}

void Context::context(struct TNode* n)
{
unsigned v;
unsigned cur;


if(n != 0)
  {
    
    switch(n->type)
    {

        case PROGRAM                    : {
                                            b.push(1); 
                                            context(n->n1); 
                                            cout<<"\nNamensliste:\n"; nl.out(); 
                                            cout<<"\nFunktionsliste:\n"; fl.out(); 
                                            cout<<"\nKonstantenliste:\n";cl.out();
                                            cout<<"\n[context] Groesse Konstanten : "<<cl.getSize()<<endl;
                                            cout<<"[context] Groesse Globale Var: "<<gp<<endl;
                                            
            
                                            char* n = fl.checkForUnImplemented();
                                            if (n!=0) 
                                            {
                                                cout<<"[context] missing implementation for prototype "<<n<<"\n";
                                                exit(-1);
                                            }
                                            if (fl.isDefined("main",0,true)==0) 
                                            {
                                                cout<<"[context] function main not implemented\n";
                                                exit(-1);
                                            }
                                            break;
                                        }
        case DECL_ST_1                  : context(n->n1); break;
        case DECL_ST_2                  : context(n->n1); context(n->n2); break;
        case DECL                       : context(n->n1); break;
        case STRUCT_DECL                : context(n->n1); context(n->n2);  break;
        case VAR_DECL_ST_1              : 
                                        {
                                            context(n->n1); /*Dekl.-Blockende*/
                                            cblock=++blockmax;
                                            b.push(cblock); //aktuelle Blocknummer auf den Stack                                           
                                            unsigned oldsp = sp;
                                            while(1)
                                            {
                                                
                                                
                                                char* c = s.first();                                            
                                                TType t = stype.firsttype();
                                                if (c==0) break;
                                                                                
                                                //if (t==svoid) cout<<"Typestack leer!";
                                                int tmpblock;
                                                bool isGlobal = false;
                                                
                                                if (s.count()<decl) 
                                                { 
                                                    tmpblock = cblock;
                                                } else if (s.count()==decl) 
                                                {
                                                  f.push(c); 
                                                  ft.push(t);
                                                  unsigned idx = fl.isProto(f.top(),par.count());
                                                  if (idx!=0) ins(idx); else ins(fl.nextId()); 
                                                  func = false;  
                                                  continue;
                                                    } else { tmpblock = 1; isGlobal = true; } // diese deklaration kommt aus dem hauptblock
                                                
                                                
                                                if (nl.isDefined(c,tmpblock)>0) 
                                                {
                                                  cout<<"[context] variable "<<c<<" in block "<<tmpblock<<" is already defined";
                                                  exit(-1);
                                                }
                                                
                                                // Adressberechnung
                                                unsigned length = (t>=slong)?4:t+1;
                                                unsigned idx = 0;
                                                if (isGlobal) // fuer globale var. aus dem hauptblock...
                                                {
                                                    gp = align(gp, length);
                                                    idx = nl.insert(c, tmpblock, t, gp, true);
                                                    gp+=length;
                                                } else      // fuer lokale var. in funktionen....
                                                {
                                                    sp = align(sp, length);                                            
                                                    idx = nl.insert(c, tmpblock, t, sp, false);                      
                                                    sp+=length;
                                                }
                                                
                                                ins(idx);                                            
                                                
                                            }
                                          // Groesse eines jeden blocks merken
                                          if (sp>maxsp) maxsp=sp;
                                          bl.push(sp-oldsp);
                                          decl = 0;
                                         
                                        }
                                        break;
        case VAR_DECL_ST_2              : decl++; // Deklarationen mitzählen, um sie von denen des hauptblocks zu unterscheiden
                                          context(n->n1); context(n->n2);  break;
        case VAR_PART_ST_1              : context(n->n1); break;
        case VAR_PART_ST_2              : context(n->n1); context(n->n2);  if (func) decl++;  break;
        case VAR_PART_ALL_ST_1          : context(n->n1); if (func) decl++;  break;
        case VAR_PART_ALL_ST_2          : context(n->n1); context(n->n2); if (func) decl++;   break;
        case VAR_DECL_1                 : context(n->n1); context(n->n2); break;
        case VAR_DECL_2                 : context(n->n1); break;
        case VAR_DECL_3                 : context(n->n1); context(n->n2); break;
        case VAR_DECL_4                 : context(n->n1); context(n->n2); break;
        case DEF_PART                   : context(n->n1); s.push((char*)n->n2); stype.push(lasttype); break;
        case STRUCT_PART                : cout<<"[context] structs not implemented\n"; exit(-1); context(n->n1); break;
        case BASE_TYPE                  : lasttype = (TType)(unsigned)n->n1; break;
        case VAR_PART_1                 : context(n->n1); context(n->n2);  stype.push(lasttype); ; break;
        case VAR_PART_2                 : context(n->n1); context(n->n2); context(n->n3);  stype.push(lasttype); break;
        case VAR_PART_ALL_1             : context(n->n1); stype.push(lasttype);  break;
        case VAR_PART_ALL_2             : context(n->n1); context(n->n2);  stype.push(lasttype);  break;
        case VAR_PART_ALL_3             : context(n->n1); context(n->n2); context(n->n3);  stype.push(lasttype);  break;
        case VAR_IDENT                  : s.push((char*)n->n1);break;
        case DIM_ST_1                   : context(n->n1); break;
        case DIM_ST_2                   : context(n->n1); context(n->n2);break;
        case ARRAY_PART                 : cout<<"[context] arrays not implemented\n"; exit(-1); context(n->n1); break;
        case DIM                        : context(n->n1); break;
        case INIT_PART                  : context(n->n1); break;
        case CONSTANT_1                 : context(n->n1); break;
        case CONSTANT_2                 : context(n->n1); break;
        case CONSTANT_3                 : minus = true; context(n->n1); minus = false; break;
        case UNSIGNED_CONSTANT          : context(n->n1); break;
        case CHAR_CONSTANT              : if(minus) cl.insert(-(char)n->n1, ++cc);  else { cl.insert((char)n->n1, ++cc); lastconst = (char)n->n1; break; }
        case INT_CONSTANT               : if(minus) cl.insert(-(int)n->n1, ++cc); else { cl.insert((int)n->n1, ++cc); lastconst = (int)n->n1; break; }
        case FLOAT_CONSTANT             : if(minus) cl.insert(-*(double*)n->n1, ++cc); else cl.insert(*(double*)n->n1, ++cc); break;
        case COMPLEX_CONSTANT_OPT       : context(n->n1); break;
        case COMPLEX_CONSTANT_ST_1      : context(n->n1); break;
        case COMPLEX_CONSTANT_ST_2      : context(n->n1); context(n->n2); break;
        case COMPLEX_CONSTANT_1         : 
        case COMPLEX_CONSTANT_2         : cout<<"[context] Complex initialisers not implemented!\n"; exit(-1); break;
        case FUNC_DECL                  : { 
                                          func = true;
                                          sp = 0; // stackpointer resetten 
                                          context(n->n1);
                                          
                                          char* c = f.top();
                                          TType* sig = (TType*)malloc(100);
                                          TType ret = ft.toptype();
                                          
                                          // prototypes
                                          if (c==0) 
                                          {
                                            c = s.top(); 
                                            s.pop(1);
                                            ret = stype.toptype();
                                            stype.pop(1); 
                                            ins(fl.nextId());                                           
                                          }
                                          
                                          if ((ret!=svoid)&&(!retu)&&(!proto))
                                          {
                                            cout<<"[context] Missing return statement in non-void function "<<c<<"\n";
                                            exit(-1);
                                          }
                                          retu = false;
                                          //strcpy(sig,"\0");
                                          unsigned num = 0;
                                          while(1)
                                          {   
                                            TType tmp = par.toptype();                                            
                                            if (tmp==undeclared) break;
                                            *(sig++)=tmp;
                                            par.pop(1);
                                            num++;
                                          }
                                          //cout<<"Name: "<<c<<" SIG: "<<sig<<"\n";
                                        
                                          
                                          if (c==0) { cout<<"funcident fehlt!"; break; }
                                          if (fl.isDefined(c,num,true)) 
                                          {
                                            cout<<"[context] function "<<c<<" with same signature already defined";
                                            exit(-1);
                                          }
                                          fl.insert(c, sig-num, ret, num, proto, maxsp);
                                          proto = false;
                                          f.pop(1);                                          
                                          ft.pop(1);
                                          func = false;
                                          maxsp = 0;
                                          
                                          
                                        }
                                          break;
        case PROTOTYPE_1                : context(n->n1); context(n->n2);  proto = true; break;
        case PROTOTYPE_2                : context(n->n1); context(n->n2); context(n->n3); proto = true; break;
        case PROTOTYPE_3                : context(n->n1); context(n->n2); proto = true;break;
        case PROTOTYPE_4                : context(n->n1); context(n->n2); context(n->n3); proto = true; break;
        case PROTOTYPE_5                : context(n->n1); proto = true; break;
        case PROTOTYPE_6                : context(n->n1); context(n->n2);  proto = true; break;
        case RET_TYPE                   : stype.push(svoid); break;
        case FUNC_IDENT                 : s.push((char*)n->n1); break;
        case PAR_TYPE_ST_1              : context(n->n1); break;
        case PAR_TYPE_ST_2              : context(n->n1); context(n->n2); break;
        case PAR_TYPE_1                 : context(n->n1); par.push(lasttype); break;
        case PAR_TYPE_2                 : context(n->n1); break;
        case IMPLEMENTATION_1           : context(n->n1); context(n->n2); context(n->n3); break;
        case IMPLEMENTATION_2           : context(n->n1); context(n->n2); context(n->n3); context(n->n4); context(n->n5); break;
        case IMPLEMENTATION_3           : context(n->n1); context(n->n2); context(n->n3); break;
        case IMPLEMENTATION_4           : context(n->n1); context(n->n2); context(n->n3); context(n->n4); context(n->n5); break;
        case IMPLEMENTATION_5           : context(n->n1); context(n->n2); break;
        case IMPLEMENTATION_6           : context(n->n1); context(n->n2); context(n->n3); context(n->n4); break;
        case PAR_DECL_ST_1              : context(n->n1); break;
        case PAR_DECL_ST_2              : context(n->n1); context(n->n2); break;
        case PAR_DECL                   : context(n->n1); context(n->n2); stype.push(lasttype); decl++; break;
        case PAR_IDENT                  : context(n->n1); s.push((char*)n->n1); break;
        case BLOCK                      : context(n->n1); context(n->n2); /*Blockende*/ b.pop(1); cblock = b.topi(0); break;
        case STM_ST_1                   : context(n->n1); break;
        case STM_ST_2                   : context(n->n1); context(n->n2);break;
        case STM                        : context(n->n1); ex = 0; break;
        case EMPTY                      : break;
        case EXPR                       : context(n->n1);break;
        case BREAK                      : break;
        case RETURN_1                   : if (ft.toptype()!=svoid) 
                                          {
                                            cout<<"[context] undefined return in non-void function "<<f.top()<<"\n";
                                            exit(-1);
                                          }                                           
                                          break;
        case RETURN_2                   : context(n->n1); 
                                          if (ft.toptype()==svoid) 
                                          {
                                            cout<<"[context] void function "<<f.top()<<" can not return anything\n"; 
                                            exit(-1);
                                          }
                                          retu = true;
                                          break;
        case IF_1                       : context(n->n1); context(n->n2); break;
        case IF_2                       : context(n->n1); context(n->n2); context(n->n3); break;
        case COND                       : context(n->n1); break;
        case SWITCH                     : 
                                        {
                                            startcount.push(startc); 
                                            startc=labelcount; 
                                            context(n->n1); context(n->n2); context(n->n3); 
                                            labelcount = startc; 
                                            startc=startcount.topi(0); 
                                            startcount.pop(1); 
                                            break;
                                        }
        case CASE_ST_1                  : context(n->n1); break;
        case CASE_ST_2                  : context(n->n1); context(n->n2); break;
        case CASE                       : context(n->n1); context(n->n2); context(n->n3);break;
        case CASE_LABEL_2               : lastconst = 0xFFFFFFFF;
        case CASE_LABEL_1               : 
                                        {
                                            context(n->n1); 
                                            for(unsigned i=startc;i<labelcount;i++)
                                            {
                                                if (lastconst==caselabels[i]) 
                                                {
                                                    if (lastconst==0xFFFFFFFF) 
                                                        cout<<"[context] default case label already definied\n";
                                                    else    cout<<"[context] case label with value "<<lastconst<<" already definied\n";
                                                    exit(-1);
                                                }
                                            }
                                            caselabels[labelcount++]=lastconst; 
                                            break;
                                        }        
        case WHILE                      : context(n->n1); context(n->n2); break;
        case COMPOUND                   : 
                                        {
                                            context(n->n1); 
                                            context(n->n2); 
                                            b.pop(1); 
                                            cblock = b.topi(0);  
                                            
                                            // alle Variablen aus dem gerade verlassenen Block sind tot, also Speicher wieder
                                            // freigeben und Stackpointer zurückschieben
                                            sp -= bl.topi(0); 
                                            bl.pop(1); 
                                            break;
                                        }
        case EXPRESSION_ST_1            : context(n->n1); break;
        case EXPRESSION_ST_2            : context(n->n1); context(n->n2); break;
        case EXPRESSION_1               : context(n->n1); ex++; break;
        case EXPRESSION_2               : context(n->n1); context(n->n2); ex++; break;
        case EQUALITY_1                 : context(n->n1); break;
        case EQUALITY_2                 : context(n->n1); context(n->n2); break;
        case EQUALITY_3                 : context(n->n1); context(n->n2); break;
        case RELATION_1                 : context(n->n1); break;
        case RELATION_2                 : context(n->n1); context(n->n2); break;
        case RELATION_3                 : context(n->n1); context(n->n2); break;
        case RELATION_4                 : context(n->n1); context(n->n2); break;
        case RELATION_5                 : context(n->n1); context(n->n2); break;
        case SHIFT_1                    : context(n->n1); break;
        case SHIFT_2                    : context(n->n1); context(n->n2); break;
        case SHIFT_3                    : context(n->n1); context(n->n2); break;
        case ADD_SUB_1                  : context(n->n1); break;
        case ADD_SUB_2                  : context(n->n1); context(n->n2); break;
        case ADD_SUB_3                  : context(n->n1); context(n->n2); break;
        case MULT_DIV_1                 : context(n->n1); break;
        case MULT_DIV_2                 : context(n->n1); context(n->n2); break;
        case MULT_DIV_3                 : context(n->n1); context(n->n2); break;
        case MULT_DIV_4                 : context(n->n1); context(n->n2); break;
        case PRIMITIVE_1                : context(n->n1); break;
        case PRIMITIVE_2                : context(n->n1); break;
        case PRIMITIVE_3                : context(n->n1); break;
        case PRIMITIVE_4                : context(n->n1); break;
        case OPERAND                    : context(n->n1); break;
        case VARIABLE                   : context(n->n1); context(n->n2); 
                                          {
                                                                            
                                          v = 0;
                                          cur = cblock;
                                          
                                          char* c = s.top();
                                          if (c==0) cout<<"********ERROR*******";
                                          
                                          while(1)
                                          {
                                            unsigned nlidx = nl.isDefined(c,cur);
                                            if (nlidx!=0)
                                            {
                                                ins(nlidx); // Namenslistenindex in Traversierung einfügen
                                                
                                            break;
                                            }
                                            cur = b.topi(v);
                                            if (cur==0) { printf("[context] variable %s in block %d undefined",c, cblock); exit(-1); }
                                            v++;
                                            
                                          }
                                          s.pop(1);
                                          }
                                                                              
                                          break;
        case QUALIFYING_1               : context(n->n1); break;
        case QUALIFYING_2               : context(n->n1); context(n->n2); break;
        case QUALIFYING_3               : context(n->n1); context(n->n2); context(n->n3);break;
        case FUNCTION_CALL_1            : {call=true; context(n->n1);call=false;

                                            char* c = s.top();
                                            unsigned idx = fl.isDefined(c, ex,false);
                                            if (idx==0) 
                                            {
                                              cout<<"[context] call to unknown function: "<<c<<"()\n";
                                              exit(-1);
                                            }
                                            s.pop(1);
                                            ins(idx);
                                          }
                                          break;
        case FUNCTION_CALL_2            : call=true; ins(0); context(n->n1); context(n->n2); context(n->n3);call=false;
                                          {
                                          char* c = s.top();
                                          
                                          unsigned idx = fl.isDefined(c, ex,false);
                                          if (idx==0) 
                                          {
                                            cout<<"[context] call to unknown function: "<<c<<"("<<ex<<" parameter(s) ) \n";
                                            exit(-1);
                                          }
                                          s.pop(1); 
                                          insrev(idx);
                                          }
        break;
        case EPSILON                    :  break;
    }
  }
}


void Context::ins(unsigned index)
{
    while(*cpos!=IDENTIFIER) cpos++;
    *(++cpos) = index;
}

void Context::insrev(unsigned index)
{
    unsigned* cposold=cpos;
    while(*cpos!=0) cpos--;
    *cpos = index;
    cpos=cposold;
}

unsigned Context::align(unsigned size, unsigned alignm) 
{
    return ((size+alignm-1)/alignm)*alignm;
} 
