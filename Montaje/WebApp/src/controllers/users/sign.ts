import models from "../../models/Index.js";
import { userSchema } from "../../types/user.js";
import { JWT_SECRET } from "../../utils/config.js";
import { compareSync, hashSync } from "bcrypt";
import { Router } from "express";
import jwt from "jsonwebtoken";


const sign = Router();

sign.post("/", async (req, res, next) => {
    try {
        const { username, password } = userSchema.parse(req.body);
        const newUser = new models.User({
            password: hashSync(password, 10),
            username
        });
        await newUser.save();
        res.status(201).send();
    } catch (error) {
        next(error);
    }
});

sign.put("/", async (req, res, next) => {
    try {
        const { username, password } = userSchema.parse(req.body);
        const user = await models.User.findOne({
            where: { username }
        });
        if (!user) {
            throw new Error(`User with username: ${username} not found`);
        }
        if (!compareSync(password, user.get("password") as string)) {
            throw new Error("Unauthorized: wrong password");
        }
        const token = jwt.sign({ id: user.get("id") }, JWT_SECRET);
        res.status(200).json({
            token: `Bearer ${token}`,
            user
        });
    } catch (error) {
        next(error);
    }
});

export default sign;
