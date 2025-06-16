import models from "../../models/Index.js";
import { signInSchema } from "../../types/signIn.js";
import { JWT_SECRET } from "../../utils/config.js";
import { compareSync, hashSync } from "bcrypt";
import { randomBytes } from "crypto";
import { Router } from "express";
import jwt from "jsonwebtoken";


const sign = Router();

sign.post("/", async (req, res, next) => {
    try {
        const newPassword = randomBytes(16).toString("hex");
        const newEsp = new models.Esp({
            password: hashSync(newPassword, 10),
            startTime: new Date()
        });
        await newEsp.save();
        res.status(201).json({
            id: newEsp.get("id"),
            password: newPassword
        });
    } catch (error) {
        next(error);
    }
});

sign.put("/", async (req, res, next) => {
    try {
        const { id, password } = signInSchema.parse(req.body);
        const esp = await models.Esp.findByPk(id, {
            attributes: ["password"]
        });
        if (!esp) {
            throw new Error("ESP id not found");
        }
        if (!compareSync(password, esp.get("password") as string)) {
            throw new Error("Invalid password for ESP with id: " + id);
        }
        const token = jwt.sign({ id: esp.get("id") }, JWT_SECRET);
        res.status(200).json({
            id: esp.get("id"),
            token: `Bearer ${token}`
        });
    } catch (error) {
        next(error);
    }
});

export default sign;
