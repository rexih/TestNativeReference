package cn.rexih.android.testnativereference.entity;

import java.util.ArrayList;


/**
 * @author huangwr
 * @version %I%, %G%
 * @package cn.rexih.android.testnativereference.entity
 * @file Product
 * @date 2018/12/7
 */
public class Product {

    private long id;
    protected String name;
    public int quantity;
    ArrayList<Service> services;


    private long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    protected String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public ArrayList<Service> getServices() {
        return services;
    }

    public void setServices(ArrayList<Service> services) {
        this.services = services;
    }

    public static String getTheName(){
        return Product.class.getSimpleName();
    }
}
