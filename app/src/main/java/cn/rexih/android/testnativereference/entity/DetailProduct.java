package cn.rexih.android.testnativereference.entity;

import java.util.ArrayList;


/**
 * @author huangwr
 * @version %I%, %G%
 * @package cn.rexih.android.testnativereference.entity
 * @file DetailProduct
 * @date 2018/12/7
 */
public class DetailProduct extends Product {

    public static int totalCount = 100;

    public int soldAmount;
    public int followAmount;
    public String[] promotions;
    public ArrayList<Review> reviews;

    @Override
    public int getQuantity() {
        return -1;
    }
}
