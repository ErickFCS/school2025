import { sequelize } from "../utils/connection.js";
import { DataTypes, Model } from "sequelize";


class User extends Model { }

User.init({
    id: {
        autoIncrement: true,
        primaryKey: true,
        type: DataTypes.INTEGER
    },
    password: {
        allowNull: false,
        type: DataTypes.STRING
    },
    username: {
        allowNull: false,
        type: DataTypes.STRING,
        unique: true
    }
}, {
    modelName: "User",
    sequelize,
    tableName: "users",
    timestamps: false
});

export default User;
